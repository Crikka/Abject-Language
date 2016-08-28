#pragma once

#include "common/cref.h"
#include "common/memory.h"

#include <iostream>

#include <memory>
#include <string>

namespace ai {
class Statement {
 public:
  enum Kind { kReturn, kStringLiteral };

  virtual ~Statement() = default;

  template <typename T>
  typename T::Type &Op() {
    return *(aop().Get<typename T::Type>(T::Index));
  }

  Kind kind() { return kind_; }

 protected:
  explicit Statement(Kind kind) : kind_(kind) {}

  template <typename... TSomething>
  void init(typename TSomething::Type *... args) {
    static constexpr size_t length = sizeof...(TSomething);

    if (length > 0) {
      data_.reset(new Memory(length + sizeof(void *)));
      recursive_intern<0, TSomething...>(args...);
    }
  }

  void store(size_t index, void *datum) { aop().Set(index, datum); }

 private:
  template <size_t N>
  void recursive_intern() {}

  template <size_t N, typename TFirst, typename... TRest>
  void recursive_intern(typename TFirst::Type *first,
                        typename TRest::Type *... rest) {
    intern<N, TFirst>(first);
    recursive_intern<N + 1, TRest...>(rest...);
  }

  template <size_t N, typename TFirst>
  void intern(typename TFirst::Type *first) {
    static_assert(TFirst::Index == N, "Invalid index for a statement!");

    aop().Set(N, first);
  }

  ArrayOfPointer aop() { return ArrayOfPointer(data_->View()); }

  std::unique_ptr<Memory> data_;
  Kind kind_;
};

class Return : public Statement {
 public:
  struct Value {
    constexpr static size_t Index = 0;
    typedef size_t Type;
  };

  Return(size_t var) : Statement(kReturn), var_(var) { init<Value>(&var_); }

 private:
  size_t var_;
};

template <typename T, Statement::Kind k>
class Assignment : public Statement {
 public:
  struct Left {
    constexpr static size_t Index = 0;
    typedef size_t Type;
  };

  struct Right {
    constexpr static size_t Index = 1;
    typedef T Type;
  };

  Assignment(size_t var, T &value) : Statement(k), var_(var), value_(value) {
    init<Left, Right>(&var_, &value);
  }

 private:
  size_t var_;
  T value_;
};

typedef Assignment<const std::string, Statement::kStringLiteral> StringLiteral;
}  // namespace ai
