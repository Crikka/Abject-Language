#include "metamodel/types.h"

#include "metamodel/module.h"

namespace ai {
Artefact::Artefact(Module *module) : Modular(module) {}
Artefact::~Artefact() {}

Model::Model(Module *module) : Artefact(module) {}
Model::~Model() {}

ArrayModel *Model::ArrayOf() { return new ArrayModel(this); }

Facet::Facet(Module *module) : Model(module) {}
Facet::~Facet() {}

Model *ArrayModel::of() const { return of_.get(); }

ArrayModel::ArrayModel(Model *of) : Model(of->module()), of_(of) {}
ArrayModel::~ArrayModel() {}

// Static
String *String::Instance() {
  static String *instance = new String();

  return instance;
}

String::String() : Model(Module::Core()) {}
String::~String() {}

}  // namespace ai
