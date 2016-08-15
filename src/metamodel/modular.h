#pragma once

#include "common/cref.h"

namespace ai {
class Module;

struct Modular {
 public:
  Modular(Module *module);
  virtual ~Modular();

  Module *module() const;

 private:
  cref<Module> module_;
};
}  // namespace ai
