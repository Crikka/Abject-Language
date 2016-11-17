#include <iostream>

#include "compiler/parser/parse.h"

#include "metamodel/metamodel.h"
#include "metamodel/types.h"

#include "metamodel/cfg/cfg.h"
#include "metamodel/cfg/identifier.h"
#include "metamodel/cfg/statements.h"

#include "abstract/abstract.h"

#include "execution/lethargy/executor.h"
#include "execution/lethargy/interpreter.h"

#include "common/memory.h"
#include "common/murmur.h"

#include <set>

int main(int argc, char* argv[]) {
  using namespace ai;

  // abject::parseFile("misc/examples/Simple.abj");

  cref<CFG> cfg(new CFG);
  cfg->Push(new StringLiteral(2, "foo"));
  cfg->Push(new Return(2));
  /*cfg->Branch();
  cfg->Trunk();*/

  /*ai::AbstractDomain domain;
  ai::Identifier id{1, 2};

  domain.Let(id) < 6;
  domain.Let(id) = 6;
  domain.Let(id) < 6;*/

  /*Memory memory(50);
  MemoryView view(memory.View());

  Executor executor(cfg, &view);
  cref<Artefact> result = executor.Start();*/

  std::set<uint64_t> set;

  for (size_t i = 0; i < 10000000000; i++) {
    uint64_t res;
    MurmurHash3_x64_128(std::to_string(i).c_str(), 1, 0, &res);

    if (!set.insert(res).second) {
      std::cerr << "Collide : " << i << std::endl;
    }
  }

  return 0;
}
