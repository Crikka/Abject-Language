#pragma once

#include "common/cref.h"

namespace ai {
class CFG;
class Artefact;
class MemoryView;

class Executor {
 public:
  explicit Executor(CFG *cfg, MemoryView *mview);

  cref<Artefact> Start();

 private:
  cref<CFG> cfg_;
  MemoryView *mview_;
};
}  // namespace ai
