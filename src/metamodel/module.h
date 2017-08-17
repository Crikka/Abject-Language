#pragma once

#include <string>

namespace ai {
class Module {
 public:
  static Module *LookFor(const std::string &identifier);
  static Module *Core();

  ~Module();

 private:
  explicit Module(const std::string &identifier);

  std::string identifier_;
};
}  // namespace ai
