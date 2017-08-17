#include "metamodel/types.h"

#include "metamodel/module.h"

namespace ai {
Artefact::Artefact(Module *module) : Modular(module) {}

Artefact::~Artefact() {}

Model::Model(Module *module, Kind kind) : Artefact(module), kind_(kind) {}

Model::~Model() {}

Model::Kind Model::kind() const { return kind_; }

ArrayModel *Model::ArrayOf() { return new ArrayModel(this); }

Facet::Facet(Module *module) : Model(module, kComplex) {}

Facet::~Facet() {}

Model *ArrayModel::of() const { return of_; }

ArrayModel::ArrayModel(Model *of) : Model(of->module(), kComplex), of_(of) {}

ArrayModel::~ArrayModel() {}

// Static
String *String::Instance() {
  static String *instance = new String;

  return instance;
}

String::String() : Model(Module::Core(), kString) {}

String::~String() {}

// Static
I32 *I32::Instance() {
  static I32 *instance = new I32;

  return instance;
}

I32::I32() : Model(Module::Core(), kI32) {}

I32::~I32() {}
}  // namespace ai
