#pragma once

#include <iostream>

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "common/memory.h"

namespace ai {
class Statement;
class Compare;
class Return;
class Call;

template <typename T>
class Assignment;

typedef Assignment<std::string> StringLiteral;
typedef Assignment<int32_t> Int32Literal;

struct Visitor {
  void Visit(Statement *statement);

  virtual void callback(Compare * /*_*/) {}
  virtual void callback(Return * /*_*/) {}
  virtual void callback(Call * /*_*/) {}
  virtual void callback(StringLiteral * /*_*/) {}
  virtual void callback(Int32Literal * /*_*/) {}
};

class Statement {
 public:
  virtual void visit(Visitor *visitor) = 0;

  virtual ~Statement() = default;

 protected:
  Statement() {}

 private:
};

class Compare : public Statement {
 public:
  enum Kind { kEq, kNEq };

  void visit(Visitor *visitor) override { visitor->callback(this); }

  explicit Compare(size_t var, size_t left, size_t right, Kind kind)
      : Statement(), var_(var), left_(left), right_(right), kind_(kind) {}

  size_t var() const { return var_; }
  size_t left() const { return left_; }
  size_t right() const { return right_; }
  Kind kind() const { return kind_; }

 private:
  size_t var_;
  size_t left_;
  size_t right_;
  Kind kind_;
};

class Return : public Statement {
 public:
  void visit(Visitor *visitor) override { visitor->callback(this); }

  Return(size_t value) : Statement(), value_(value) {}

  size_t value() const { return value_; }

 private:
  size_t value_;
};

class Call : public Statement {
 public:
  void visit(Visitor *visitor) override { visitor->callback(this); }

  Call(size_t function_id, size_t var, const std::vector<size_t> &args)
      : Statement(), function_id_(function_id), var_(var), args_(args) {}

  size_t function_id() const { return function_id_; }
  size_t var() const { return var_; }
  const std::vector<size_t> &args() const { return args_; }

 private:
  size_t function_id_;
  size_t var_;
  std::vector<size_t> args_;
};

template <typename T>
class Assignment : public Statement {
 public:
  void visit(Visitor *visitor) override { visitor->callback(this); }

  Assignment(size_t var, const T &value)
      : Statement(), var_(var), value_(value) {}

  size_t var() const { return var_; }
  const T &value() const { return value_; }

 private:
  size_t var_;
  T value_;
};

#undef DeclareAs
}  // namespace ai
