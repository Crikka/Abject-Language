#include "metamodel/metamodel.h"

#include <cassert>
#include <memory>

#include "metamodel/function.h"
#include "metamodel/types.h"

namespace ai {
static std::unique_ptr<Metamodel> instance;

Metamodel *model() {
  if (!instance) instance.reset(new Metamodel);

  return instance.get();
}

Metamodel::Metamodel() {}

Metamodel::~Metamodel() {}

Function *Metamodel::AddFunction(Model *return_type, Code *code,
                                 const std::string &name) {
  Function *function = new Function(return_type, code, name);
  function->id(functions_.size());
  functions_.emplace_back(function);

  return function;
}

Function *Metamodel::function(size_t pos) {
  assert(pos < functions_.size());

  return functions_[pos].get();
}

}  // namespace ai
