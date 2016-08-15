#pragma once

#include "common/cref.h"

namespace ai {
class CFG;
class Model;
class MemoryView;

class Executor {
public:
  explicit Executor(CFG *cfg, MemoryView *mview);

  cref<Model> Start();

private:
  cref<CFG> cfg_;
  MemoryView *mview_;
};
}  // namespace ai
