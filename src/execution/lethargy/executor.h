#pragma once

#include <stddef.h>
#include <vector>

#include "common/unique.h"

namespace ai {
class Metamodel;

namespace rt {
class Value;

class Executor {
 public:
  explicit Executor(Metamodel *metamodel);
  virtual ~Executor();

  Value *Start(size_t function_id, const std::vector<Value *> args);

 private:
  struct Impl;
  unique<Impl> impl;
};
}  // namespace rt
}  // namespace ai
