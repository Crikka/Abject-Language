//===--- examples/Fibonacci/fibonacci.cpp - An example use of the JIT -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This small program provides an example of how to build quickly a small module
// with function Fibonacci and execute it with the JIT.
//
// The goal of this snippet is to create in the memory the LLVM module
// consisting of one function as follow:
//
//   int fib(int x) {
//     if(x<=2) return 1;
//     return fib(x-1)+fib(x-2);
//   }
//
// Once we have this, we compile the module via JIT, then execute the `fib'
// function and return result to a driver, i.e. to a "host program".
//
//===----------------------------------------------------------------------===//

#include <algorithm>
#include <cstdlib>
#include <memory>
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

#include <iostream>

#include "compiler/parser/ast.h"
#include "compiler/parser/parse.h"

#include "metamodel/function.h"
#include "metamodel/metamodel.h"
#include "metamodel/types.h"

#include "metamodel/cfg/code.h"
#include "metamodel/cfg/identifier.h"
#include "metamodel/cfg/statements.h"

#include "execution/onirism/backend.h"

using namespace llvm;

/*static Function *CreateFibFunction(LLVMContext &ctx, Module *M) {
  // Get pointers to the constants.
  Value *One = ConstantInt::get(Type::getInt32Ty(ctx), 1);
  Value *Two = ConstantInt::get(Type::getInt32Ty(ctx), 2);

  // Get pointer to the integer argument of the add1 function...
  Argument *ArgX = &*FibF->arg_begin();  // Get the arg.
  ArgX->setName("n");  // Give it a nice symbolic name for fun.

  // Create the true_block.
  BasicBlock *RetBB = BasicBlock::Create(ctx, "return", FibF);
  // Create an exit block.
  BasicBlock *RecurseBB = BasicBlock::Create(ctx, "recurse", FibF);

  // Create the "if (arg <= 2) goto exitbb"
  Value *CondInst = new ICmpInst(*BB, ICmpInst::ICMP_SLE, ArgX, Two, "cond");
  BranchInst::Create(RetBB, RecurseBB, CondInst, BB);

  // Create: ret int 1
  ReturnInst::Create(ctx, One, RetBB);

  // create fib(x-1)
  Value *Sub = BinaryOperator::CreateSub(ArgX, One, "arg", RecurseBB);
  CallInst *CallFibX1 = CallInst::Create(FibF, Sub, "fibx1", RecurseBB);
  CallFibX1->setTailCall();

  // create fib(x-2)
  Sub = BinaryOperator::CreateSub(ArgX, Two, "arg", RecurseBB);
  CallInst *CallFibX2 = CallInst::Create(FibF, Sub, "fibx2", RecurseBB);
  CallFibX2->setTailCall();

  // fib(x-1)+fib(x-2)
  Value *Sum =
      BinaryOperator::CreateAdd(CallFibX1, CallFibX2, "addresult", RecurseBB);

  // Create the return instruction and add it to the basic block
  ReturnInst::Create(ctx, Sum, RecurseBB);

  return FibF;
}*/

int main(int argc, char **argv) {
  ai::ast::Program *program =
      ai::parsing::parse_file("misc/examples/Simple.abj");
  std::cerr << "module : " << program->module << " -> "
            << program->top_level_contents.size() << std::endl;

  return 0;

  /*ai::Code *code = new ai::Code;
  code->Push(new ai::StringLiteral(2, "foo"));
  code->Push(new ai::Int32Literal(1, 5));
  code->Push(new ai::Call(1, 0, {2}));
  code->Push(new ai::Return(0));

  ai::Function *main = meta.AddFunction(new ai::Function(code));
  main->parameters(0);
  main->locals(3);

  ai::Code *code2 = new ai::Code;
  code2->Push(new ai::Return(0));

  ai::Function *identity = meta.AddFunction(new ai::Function(code2));
  identity->parameters(1);
  identity->locals(1);*/

  /*ai::AbstractDomain domain;
  ai::Identifier id{1, 2};

  domain.Let(id) < 6;
  domain.Let(id) = 6;
  domain.Let(id) < 6;*/

  /*ai::Code *code = new ai::Code;
  ai::Block *entry = code->EntryBlock();
  entry->Push(new ai::Call(1, 0, {}));
  entry->Push(new ai::Int32Literal(1, 0));
  entry->Push(new ai::Compare(2, 0, 1, ai::Compare::kEq));

  std::pair<ai::Block *, ai::Block *> follow = code->Branch(entry, 2);
  follow.first->Push(new ai::Int32Literal(3, 25));
  follow.second->Push(new ai::Int32Literal(4, 42));
  follow.first->Push(new ai::Return(3));
  follow.second->Push(new ai::Return(4));

  ai::Function *main =
      ai::model()->AddFunction(ai::I32::Instance(), code, "main");
  main->locals(5);

  ai::Code *code2 = new ai::Code;
  ai::Block *entry2 = code2->EntryBlock();
  entry2->Push(new ai::Int32Literal(0, 32));
  entry2->Push(new ai::Return(0));

  ai::Function *id = ai::model()->AddFunction(ai::I32::Instance(), code2, "id");
  id->locals(1);

  ai::rt::OnirismBackend backend;
  int result = backend.RunMain(main, {});

  return result;*/
}
