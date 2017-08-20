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

  Metamodel *meta = model();

  Code *code = new Code;
  Block *entry = code->EntryBlock();
  entry->Push(new StringLiteral(2, "foo"));
  entry->Push(new Int32Literal(1, 5));
  entry->Push(new Call(1, 0, {2}));
  entry->Push(new Return(0));

  Function *main = meta->AddFunction(I32::Instance(), code, "main");
  main->locals(3);

  Code *code2 = new Code;
  Block *entry2 = code->EntryBlock();
  entry2->Push(new Return(0));

  Function *identity = meta->AddFunction(String::Instance(), code2, "id");
  identity->AddParameter(String::Instance());
  identity->locals(1);

  /*ai::AbstractDomain domain;
  ai::Identifier id{1, 2};

  domain.Let(id) < 6;
  domain.Let(id) = 6;
  domain.Let(id) < 6;*/

  rt::Executor executor(meta);
  rt::Value *result = executor.Start(0, {});

  std::cerr << static_cast<rt::Str *>(result)->value << std::endl;

  return 0;
}
