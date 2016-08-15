#pragma once

#include "metamodel/cfg/identifier.h"

#include "common/cref.h"

#include <iostream>

#include <memory>
#include <string>

namespace ai {
class Statement {
 public:
  enum Kind { kStringLiteral };

  virtual ~Statement() { free(data_); }

  template <typename T>
  typename T::Type &Op() {
    return *(reinterpret_cast<typename T::Type *>(data_[T::Index]));
  }

  Kind kind() { return kind_; }

 protected:
  explicit Statement(size_t size, Kind kind)
      : data_(reinterpret_cast<void **>(malloc(size * sizeof(void *)))),
        kind_(kind) {}

  void store(size_t index, void *datum) { data_[index] = datum; }

  template <typename T>
  void release() {
    delete reinterpret_cast<typename T::Type *>(data_[T::Index]);
  }

 private:
  void **data_;
  Kind kind_;
};

class StringLiteral : public Statement {
 public:
  struct Left {
    constexpr static size_t Index = 0;
    typedef Identifier Type;
  };

  struct Right {
    constexpr static size_t Index = 1;
    typedef std::string Type;
  };

  StringLiteral(Identifier *var, const std::string &value)
      : Statement(2, kStringLiteral), var_(var), value_(value) {
    store(0, var_.get());
    store(1, &value_);
  }

 private:
  std::unique_ptr<Identifier> var_;
  std::string value_;
};
}  // namespace ai
