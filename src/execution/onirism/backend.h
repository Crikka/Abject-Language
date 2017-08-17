#pragma once

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "execution/backend.h"

namespace ai {
namespace rt {
class OnirismBackend : public Backend {
 public:
  OnirismBackend();
  virtual ~OnirismBackend();

  int RunMain(Function *fct, const std::vector<std::string> &args) override;

 private:
};
}  // namespace rt
}  // namespace ai
