#pragma once

#include <iostream>

#include <assert.h>
#include <memory>
#include <string>

#include "common/cref.h"
#include "common/memory.h"

namespace ai {
enum StKind { kStReturn, kStStringLiteral, kStIntegerLiteral };

namespace {
template <StKind kind>
struct AsHelper {};
}

#define DeclareAs(type, kind) \
  namespace {                 \
  template <>                 \
  struct AsHelper<kind> {     \
    typedef type ReturnType;  \
  };                          \
  }

class Statement {
 public:
  virtual ~Statement() = default;

  StKind kind() const { return kind_; }

  template <StKind kind>
  typename AsHelper<kind>::ReturnType *As() {
    assert(kind == kind_);

    return static_cast<typename AsHelper<kind>::ReturnType *>(this);
  }

 protected:
  explicit Statement(StKind kind) : kind_(kind) {}

 private:
  StKind kind_;
};

class Return : public Statement {
 public:
  Return(size_t value) : Statement(kStReturn), value_(value) {}

  size_t value() const { return value_; }

 private:
  size_t value_;
};

DeclareAs(Return, kStReturn);

template <typename T, StKind k>
class Assignment : public Statement {
 public:
  Assignment(size_t var, const T &value)
      : Statement(k), var_(var), value_(value) {}

  size_t var() const { return var_; }
  const T &value() const { return value_; }

 private:
  size_t var_;
  T value_;
};

typedef Assignment<const std::string, kStStringLiteral> StringLiteral;
typedef Assignment<int, kStIntegerLiteral> IntegerLiteral;

DeclareAs(StringLiteral, kStStringLiteral);
DeclareAs(IntegerLiteral, kStIntegerLiteral);

#undef DeclareAs
}  // namespace ai
