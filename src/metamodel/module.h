#pragma once

#include "tools/countable.h"

#include <string>

namespace abject {
class Module : public Countable {
 public:
  static Module *LookFor(const std::string &identifier);
  ~Module();

 private:
  explicit Module(const std::string &identifier);

  std::string identifier_;
};
}  // namespace abject
