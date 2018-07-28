#pragma once

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "execution/backend.h"

namespace ai {
namespace rt {
class LLVMBackend : public Backend {
 public:
  LLVMBackend();
  virtual ~LLVMBackend();

  int RunMain(Function *fct, const std::vector<std::string> &args) override;

 private:
};
}  // namespace rt
}  // namespace ai
