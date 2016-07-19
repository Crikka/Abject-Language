#pragma once

#include "metamodel/cfg/identifier.h"

#include <string>

namespace abject {
struct Instruction {
  enum ID { kAssignment, kStringLiteral };

  Instruction(ID id) : id_(id) {}
  virtual ~Instruction() = default;

  ID id() const { return id_; }

 private:
  ID id_;
};

struct Assignment : public Instruction {
  Assignment(const Identifier &left, const Identifier &right)
      : Instruction(kAssignment), left_(left), right_(right) {}

  virtual ~Assignment() = default;

  const Identifier &left() const { return left_; }
  const Identifier &right() const { return right_; }

 private:
  Identifier left_, right_;
};

struct StringLiteral : public Instruction {
  StringLiteral(const Identifier &left, const std::string &right)
      : Instruction(kStringLiteral), left_(left), right_(right)  {}

  virtual ~StringLiteral() = default;

  const Identifier &left() const { return left_; }
  const std::string &right() const { return right_; }

 private:
  Identifier left_;
  std::string right_;
};
}  // namespace abject
