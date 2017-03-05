#include <iostream>

#include "compiler/parser/parse.h"

#include "metamodel/function.h"
#include "metamodel/metamodel.h"
#include "metamodel/types.h"

#include "metamodel/cfg/code.h"
#include "metamodel/cfg/identifier.h"
#include "metamodel/cfg/statements.h"

#include "abstract/abstract.h"

#include "execution/lethargy/executor.h"
#include "execution/lethargy/interpreter.h"
#include "execution/lethargy/runtime.h"

#include "common/memory.h"
#include "common/murmur.h"

#include <set>

int main(int argc, char *argv[]) {
  using namespace ai;

  // abject::parseFile("misc/examples/Simple.abj");

  Metamodel meta;

  Code *code = new Code;
  code->Push(new StringLiteral(2, "foo"));
  code->Push(new IntegerLiteral(1, 5));
  code->Push(new DirectCall(1, 0, {2}));
  code->Push(new Return(0));

  meta.AddFunction(new Function(0, 3, code));

  Code *code2 = new Code;
  code2->Push(new Return(0));

  meta.AddFunction(new Function(1, 1, code2));

  /*ai::AbstractDomain domain;
  ai::Identifier id{1, 2};

  domain.Let(id) < 6;
  domain.Let(id) = 6;
  domain.Let(id) < 6;*/

  Executor executor(&meta);
  rt::Value *result = executor.Start(0, {});

  std::cerr << static_cast<rt::Str *>(result)->value << std::endl;

  return 0;
}
