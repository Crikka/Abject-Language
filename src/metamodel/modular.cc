#include "metamodel/modular.h"

#include "metamodel/module.h"

namespace abject {
Modular::Modular(Module *module) : module_(module) {}
Modular::~Modular() {}

Module *Modular::module() const { return module_.get(); }

}  // namespace abject
