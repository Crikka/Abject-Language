#include "metamodel/metamodel.h"

#include <assert.h>

#include "metamodel/function.h"
#include "metamodel/types.h"

namespace ai {
Metamodel::Metamodel() {}

Metamodel::~Metamodel() {}

void Metamodel::AddFunction(Function *function) {
  assert(!function->IsWellDefined());

  function->id(functions_.size());
  functions_.emplace_back(function);
}

Function *Metamodel::function(size_t pos) {
  assert(pos < functions_.size());

  return functions_[pos].get();
}

}  // namespace ai
