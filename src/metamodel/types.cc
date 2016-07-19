#include "metamodel/types.h"

#include "metamodel/module.h"

namespace abject {
Artefact::Artefact(Module *module) : Modular(module) {}

Artefact::~Artefact() {}

Model::Model(Module *module) : Artefact(module) {}

Model::~Model() {}

Facet::Facet(Module *module) : Model(module) {}

Facet::~Facet() {}

}  // namespace abject
