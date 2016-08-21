#pragma once

#include "metamodel/cfg/identifier.h"

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
    return *(data_->View().AsArrayOfPointer().Get<typename T::Type>(T::Index));
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

  void store(size_t index, void *datum) {
    data_->View().AsArrayOfPointer().Set(index, datum);
  }

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

    data_->View().AsArrayOfPointer().Set(N, first);
  }

  std::unique_ptr<Memory> data_;
  Kind kind_;
};

class Return : public Statement {
 public:
  struct Value {
    constexpr static size_t Index = 0;
    typedef Identifier Type;
  };

  Return(Identifier *var) : Statement(kReturn), var_(var) {
    init<Value>(var_.get());
  }

 private:
  std::unique_ptr<Identifier> var_;
};

class StringLiteral : public Statement {
 public:
  struct Left {
    constexpr static size_t Index = 0;
    typedef Identifier Type;
  };

  struct Right {
    constexpr static size_t Index = 1;
    typedef const std::string Type;
  };

  StringLiteral(Identifier *var, const std::string &value)
      : Statement(kStringLiteral), var_(var), value_(value) {
    init<Left, Right>(var_.get(), &value);
  }

 private:
  std::unique_ptr<Identifier> var_;
  std::string value_;
};
}  // namespace ai
