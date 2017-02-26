#pragma once

#include <string>

namespace ai {
namespace rt {
struct Value {
  enum Kind { kStr, kInt };

  Value(Kind kind) : kind(kind) {}

  Kind kind;
};

struct Str : public Value {
  Str() : Value(kStr) {}

  std::string value;
};

struct Int : public Value {
  Int() : Value(kInt) {}

  int value;
};
}  // namespace rt
}  // namespace ai
