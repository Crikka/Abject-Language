#pragma once

#include <iostream>

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "common/memory.h"

namespace ai {
class Statement;
class Return;
class Call;
class Block;

template <typename T>
class Assignment;

typedef Assignment<std::string> StringLiteral;
typedef Assignment<int32_t> Int32Literal;

struct Visitor {
  void Visit(Statement *statement);

  virtual void callback(Return * /*_*/) {}
  virtual void callback(Call * /*_*/) {}
  virtual void callback(Block * /*_*/) {}
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

class Block : public Statement {
 public:
  void visit(Visitor *visitor) override { visitor->callback(this); }

  Block();

  void AddStatement(Statement *statement);
  const std::vector<std::unique_ptr<Statement>> &statements() const;

 private:
  std::vector<std::unique_ptr<Statement>> statements_;
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
