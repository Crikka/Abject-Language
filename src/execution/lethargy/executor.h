#pragma once

#include <stddef.h>
#include <vector>

#include "common/cref.h"
#include "common/unique.h"

namespace ai {
namespace rt {
struct Value;
}  // namespace rt

class Metamodel;

class Executor {
 public:
  explicit Executor(Metamodel *metamodel);
  virtual ~Executor();

  rt::Value *Start(size_t function_id, const std::vector<rt::Value *> args);

 private:
  struct Impl;
  unique<Impl> impl;
};
}  // namespace ai
