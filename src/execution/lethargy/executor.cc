#include "execution/lethargy/executor.h"

#include <vector>

#include "common/memory.h"

#include "metamodel/cfg/code.h"
#include "metamodel/cfg/statements.h"
#include "metamodel/function.h"
#include "metamodel/metamodel.h"
#include "metamodel/types.h"

#include "execution/lethargy/runtime.h"

namespace ai {
namespace rt {
static rt::Value *Call(Metamodel *metamodel, size_t function_id,
                       const std::vector<rt::Value *> &args);
static rt::Value *Eval(Metamodel *metamodel, Code *code,
                       std::vector<rt::Value *> &&locals);

struct Executor::Impl {
  Metamodel *metamodel;
};

Executor::Executor(Metamodel *metamodel) : impl(new Impl) {
  impl->metamodel = metamodel;
}

Executor::~Executor() {}

rt::Value *Executor::Start(size_t function_id,
                           const std::vector<rt::Value *> args) {
  return Call(impl->metamodel, function_id, args);
}

// static
rt::Value *Call(Metamodel *metamodel, size_t function_id,
                const std::vector<rt::Value *> &args) {
  Function *fct = metamodel->function(function_id);

  size_t parameter_accepted = fct->number_of_parameters();
  size_t locals_length = fct->locals();
  Code *code = fct->code();

  assert(args.size() == parameter_accepted);
  assert(locals_length >= parameter_accepted);

  std::vector<rt::Value *> locals(locals_length, nullptr);
  for (size_t i = 0; i < parameter_accepted; i++) {
    locals[i] = args[i];
  }

  return Eval(metamodel, code, std::move(locals));
}

// static
rt::Value *Eval(Metamodel *metamodel, Code *code,
                std::vector<rt::Value *> &&locals) {
  struct ExecutorVisitor : Visitor {
    using Visitor::callback;

    ExecutorVisitor(Metamodel *metamodel, std::vector<rt::Value *> &&locals)
        : metamodel(metamodel), locals(std::move(locals)) {}

    rt::Value *result = nullptr;
    Metamodel *metamodel;
    std::vector<rt::Value *> &&locals;

    void callback(Return *ret) override { result = locals[ret->value()]; }

    void callback(ai::Call *call) override {
      size_t var = call->var();
      size_t function_id = call->function_id();
      std::vector<size_t> args_index = call->args();
      size_t args_size = args_index.size();

      std::vector<rt::Value *> args(args_size);
      for (size_t i = 0; i < args_size; i++) {
        args[i] = locals[args_index[i]];
      }

      locals[var] = Call(metamodel, function_id, args);
    }

    void callback(StringLiteral *literal) override {
      size_t left = literal->var();
      const std::string &right = literal->value();

      Str *value = new Str();
      value->value = right;

      locals[left] = value;
    }

    void callback(Int32Literal *literal) override {
      size_t left = literal->var();
      int right = literal->value();

      rt::Int *value = new rt::Int();
      value->value = right;

      locals[left] = value;
    }
  };

  ExecutorVisitor visitor(metamodel, std::move(locals));

  for (const unique<Statement> &statement : code->EntryBlock()->statements()) {
    visitor.Visit(statement.get());
    if (visitor.result) break;
  }

  return visitor.result;
}
}  // namespace rt
}  // namespace ai
