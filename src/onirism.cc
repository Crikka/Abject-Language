#include <iostream>

#include "compiler/parser/parse.h"

#include "metamodel/metamodel.h"

#include "metamodel/cfg/cfg.h"
#include "metamodel/cfg/identifier.h"
#include "metamodel/cfg/statements.h"

int main(int argc, char* argv[]) {
  // abject::parseFile("misc/examples/Simple.abj");

  ai::CFG cfg;
  cfg.Push(new ai::StringLiteral(new ai::Identifier{1, 2}, "foo"));
  cfg.Branch();
  cfg.Trunk();

  return 0;
}
