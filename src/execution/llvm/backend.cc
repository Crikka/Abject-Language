#include "execution/llvm/backend.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include <llvm/ADT/APInt.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include "common/memory.h"

#include "metamodel/cfg/code.h"
#include "metamodel/cfg/statements.h"
#include "metamodel/function.h"
#include "metamodel/metamodel.h"
#include "metamodel/types.h"

int print(const char *msg) {
  std::cerr << msg << std::endl;

  return 0;
}

namespace ai {
namespace rt {
struct LLVMInfo {
  llvm::LLVMContext *context;
  llvm::Module *module;
  Metamodel *mm;

  llvm::Function *GetFunction(size_t fct_id);
  llvm::Type *GetType(Model *model);

  std::vector<llvm::Function *> fcts;
};

LLVMBackend::LLVMBackend() {}

LLVMBackend::~LLVMBackend() {}

int LLVMBackend::RunMain(Function *fct, const std::vector<std::string> &args) {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  llvm::LLVMContext context;

  // Create some module to put functions into it.
  std::unique_ptr<llvm::Module> owner(new llvm::Module("main", context));
  llvm::Module *module = owner.get();

  LLVMInfo info;

  info.context = &context;
  info.module = module;
  info.mm = model();

  /*llvm::Function *wrapped_print = llvm::Function::Create(
      llvm::TypeBuilder<int(char *), false>::get(context),
      llvm::Function::ExternalLinkage, "print", module);*/

  llvm::Function *main = info.GetFunction(fct->id());

  std::string errStr;
  llvm::ExecutionEngine *engine =
      llvm::EngineBuilder(std::move(owner)).setErrorStr(&errStr).create();

  // engine->addGlobalMapping(wrapped_print, reinterpret_cast<void *>(&print));

  if (!engine) {
    llvm::errs() << ": Failed to construct ExecutionEngine: " << errStr << "\n";
    return 1;
  }

  llvm::errs() << "We just constructed this LLVM module:\n\n---------\n"
               << *module;

  llvm::errs() << "verifying...\n";
  if (llvm::verifyModule(*module, &llvm::errs())) {
    llvm::errs() << "Error constructing function!\n";
    return 1;
  }

  int result = engine->runFunctionAsMain(main, {}, nullptr);

  return result;
}

struct ExecutorVisitor : Visitor {
  using Visitor::callback;

  ExecutorVisitor(LLVMInfo *info, Function *function)
      : info(info),
        metamodel(info->mm),
        context(*info->context),
        module(info->module) {
    llvm::Type *return_type = info->GetType(function->return_type());
    std::vector<llvm::Type *> args_type;

    for (const std::pair<Model *, std::string> &param :
         function->parameters()) {
      args_type.push_back(info->GetType(param.first));
    }

    fct = llvm::cast<llvm::Function>(module->getOrInsertFunction(
        function->name(),
        llvm::FunctionType::get(return_type, args_type, false)));

    values.resize(function->locals(), nullptr);
    blocks.resize(function->code()->number_of_blocks(), nullptr);

    for (const std::unique_ptr<Block> &block : function->code()->blocks()) {
      current = llvm::BasicBlock::Create(context, "", fct);
      blocks[block->id()] = current;

      for (const unique<Statement> &statement : block->statements()) {
        Visit(statement.get());
      }
    }

    for (const Code::BlockGraph &graph : function->code()->block_graph()) {
      assert(values[graph.val]);

      assert(blocks[graph.from]);
      assert(blocks[graph.consequent]);
      assert(blocks[graph.alternate]);

      llvm::BranchInst::Create(blocks[graph.consequent],
                               blocks[graph.alternate], values[graph.val],
                               blocks[graph.from]);
    }
  }

  LLVMInfo *info;
  Metamodel *metamodel;
  llvm::LLVMContext &context;
  llvm::Module *module;

  llvm::Function *fct;

  llvm::Function *wrapped_print;

  llvm::BasicBlock *current;
  std::vector<llvm::BasicBlock *> blocks;
  std::vector<llvm::Value *> values;

  void callback(Compare *cmp) override {
    size_t var = cmp->var();
    size_t left = cmp->left();
    size_t right = cmp->right();

    assert(!values[var]);
    assert(values[left]);
    assert(values[right]);

    switch (cmp->kind()) {
      case Compare::kEq: {
        values[var] = new llvm::ICmpInst(*current, llvm::ICmpInst::ICMP_EQ,
                                         values[left], values[right]);
      } break;
      case Compare::kNEq: {
        values[var] = new llvm::ICmpInst(*current, llvm::ICmpInst::ICMP_NE,
                                         values[left], values[right]);
      }
    }
  }

  void callback(Return *ret) override {
    size_t value = ret->value();
    assert(values[value] != nullptr);

    /*llvm::CallInst::Create(wrapped_print, {values[value]}, "call",
                           blocks.top());*/

    llvm::ReturnInst::Create(context, values[value], current);
  }

  void callback(ai::Call *call) override {
    size_t var = call->var();
    size_t function_id = call->function_id();
    std::vector<size_t> args_index = call->args();
    size_t args_size = args_index.size();

    llvm::Function *callee = info->GetFunction(function_id);

    values[var] = llvm::CallInst::Create(callee, {}, "", current);
  }

  void callback(StringLiteral *literal) override {
    size_t left = literal->var();
    const std::string &right = literal->value();

    llvm::Constant *data = llvm::ConstantDataArray::getString(context, right);

    llvm::GlobalVariable *cst =
        llvm::cast<llvm::GlobalVariable>(module->getOrInsertGlobal(
            "lit", llvm::ArrayType::get(llvm::Type::getInt8Ty(context), 6)));

    cst->setInitializer(data);

    llvm::GetElementPtrInst *ptr_data =
        llvm::GetElementPtrInst::Create(nullptr, cst, {}, "ptr_data", current);

    values[left] = llvm::BitCastInst::CreatePointerCast(
        ptr_data, llvm::Type::getInt8Ty(context)->getPointerTo(0), "casted",
        current);
  }

  void callback(Int32Literal *literal) override {
    size_t left = literal->var();
    int32_t right = literal->value();

    values[left] =
        llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(context), right);
  }
};

llvm::Function *LLVMInfo::GetFunction(size_t fct_id) {
  if (fct_id >= fcts.size()) {
    fcts.resize(fct_id + 1, nullptr);
  }

  if (!fcts[fct_id]) {
    Function *fct = mm->function(fct_id);

    ExecutorVisitor visitor(this, fct);
    fcts[fct_id] = visitor.fct;
  }

  return fcts[fct_id];
}

llvm::Type *LLVMInfo::GetType(Model *model) {
  if (model->kind() == Model::kI32) return llvm::Type::getInt32Ty(*context);

  throw "fail!";
}

}  // namespace rt
}  // namespace ai
