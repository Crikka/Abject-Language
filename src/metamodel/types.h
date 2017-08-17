#pragma once

#include "metamodel/modular.h"

namespace ai {
class ArrayModel;

/**
*@brief The Artefact class
* Artefact is something like "Object" for OOP language.
*/
class Artefact : public Modular {
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
  enum Kind { kComplex, kString, kI32 };

  explicit Model(Module *module, Kind kind);
  virtual ~Model();

  Kind kind() const;

  ArrayModel *ArrayOf();

 private:
  Kind kind_;
};

class Facet : public Model {
 public:
  Facet(Module *module);
  virtual ~Facet();

 private:
};

class ArrayModel : public Model {
 public:
  Model *of() const;

  ~ArrayModel();

 private:
  ArrayModel(Model *of);

  Model *of_;

  friend class Model;
};

// Primitive bellow
class String : public Model {
 public:
  static String *Instance();
  virtual ~String();

 private:
  String();
};

class I32 : public Model {
 public:
  static I32 *Instance();
  virtual ~I32();

 private:
  I32();
};

}  // namespace ai
