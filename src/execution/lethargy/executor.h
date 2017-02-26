#pragma once

#include "common/cref.h"

#include <stddef.h>

namespace ai {
namespace rt {
struct Value;
}  // namespace rt

class Code;
class Artefact;
class MemoryView;

class Executor {
 public:
  explicit Executor();

  rt::Value *Start(Code *code, size_t locals_count);

 private:
};
}  // namespace ai
