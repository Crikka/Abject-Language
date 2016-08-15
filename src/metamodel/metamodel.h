#pragma once

#include "common/countable.h"
#include "common/cref.h"

#include <vector>

namespace ai {
class Model;

class Metamodel : public Countable {
 public:
  Metamodel();
  virtual ~Metamodel();

 private:
  std::vector<cref<Model>> models_;
};
}  // namespace ai
