#pragma once

#include "tools/cref.h"

#include <vector>

namespace ai {
class Model;

class Metamodel {
 public:
 private:
  std::vector<cref<Model>> models_;
};
}  // namespace ai
