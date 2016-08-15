#pragma once

#include "common/cref.h"

namespace ai {
class Metamodel;
class Module;

class Interpreter {
public:
  explicit Interpreter(Metamodel *metamodel);

  void Start(Module *module);

private:
  cref<Metamodel> metamodel_;
};
}  // namespace ai
