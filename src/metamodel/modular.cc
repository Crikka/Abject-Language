#include "metamodel/modular.h"

#include "metamodel/module.h"

namespace ai {
Modular::Modular(Module *module) : module_(module) {}

Modular::~Modular() {}

Module *Modular::module() const { return module_; }

}  // namespace ai
