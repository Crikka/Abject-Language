#pragma once

#include "tools/cref.h"

namespace abject {
class Module;

struct Modular {
 public:
  Modular(Module *module);
  virtual ~Modular();

 private:
  cref<Module> module_;
};
}  // namespace abject
