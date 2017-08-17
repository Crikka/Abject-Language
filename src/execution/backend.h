#pragma once

#include <cstdlib>
#include <string>
#include <vector>

namespace ai {
class Function;

namespace rt {
class Backend {
 public:
  Backend();
  virtual ~Backend();

  virtual int RunMain(Function *fct, const std::vector<std::string> &args) = 0;
};
}  // namespace rt
}  // namespace ai
