#include <iostream>

#include "compiler/parser/parse.h"

#include "metamodel/metamodel.h"

#include "metamodel/cfg/identifier.h"
#include "metamodel/cfg/cfg.h"
#include "metamodel/cfg/instructions.h"


int main(int argc, char* argv[]) {
  // abject::parseFile("misc/examples/Simple.abj");

  abject::CFG cfg;
  cfg.Push(new abject::StringLiteral(abject::Identifier{1, 2}, "foo"));
  cfg.Branch();
  cfg.Trunk();

  return 0;
}
