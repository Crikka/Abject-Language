#pragma once

#include <vector>

#include "common/countable.h"
#include "common/cref.h"
#include "common/unique.h"

namespace ai {
class Model;
class Function;

class Metamodel : public Countable {
 public:
  Metamodel();
  virtual ~Metamodel();

  Function *AddFunction(Function *function);

  Function *function(size_t pos);

 private:
  std::vector<unique<Model>> models_;
  std::vector<unique<Function>> functions_;
};
}  // namespace ai
