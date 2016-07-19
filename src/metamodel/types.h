#pragma once

#include "tools/countable.h"

#include "metamodel/modular.h"

namespace abject {
  /**
 * @brief The Artefact class
 * Artefact is something like "Object" for OOP language.
 */
class Artefact : public Modular, public Countable {
 public:
  Artefact(Module *module);
  virtual ~Artefact();

 private:
};

/**
 * @brief The Model class
 * A model is something like "Class" for OOP language.
 */
class Model : public Artefact {
 public:
  Model(Module *module);
  virtual ~Model();

 private:
};

class Facet : public Model {
public:
 Facet(Module *module);
 virtual ~Facet();

private:
};

}  // namespace abject
