#pragma once

#include <vector>

#include "common/unique.h"

namespace ai {
class Model;
class Function;
class Code;

class Metamodel {
 public:
  virtual ~Metamodel();

  Function *AddFunction(Model *return_type, Code *code,
                        const std::string &name = "");

  Function *function(size_t pos);

 private:
  Metamodel();

  std::vector<unique<Model>> models_;
  std::vector<unique<Function>> functions_;

  friend Metamodel *model();
};

Metamodel *model();
}  // namespace ai
