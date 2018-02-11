#pragma once

#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "common/unique.h"

namespace ai {
namespace ast {
// Forward
struct TopLevelContent;
struct Statement;
struct Value;
struct Type;
struct Signature;
struct Code;
struct VariableDeclarator;
struct Reference;

struct Program {
  std::string module;
  std::vector<unique<TopLevelContent>> top_level_contents;
};

struct TopLevelContent {};

struct Define : public TopLevelContent {
  unique<Type> on;
  unique<Signature> signature;
  unique<Code> code;
};

struct Code {
  std::vector<unique<Statement>> statements;
};

// Statements
struct Statement {};

struct Empty : public Statement {};

struct VariablesDeclaration : public Statement {
  std::vector<unique<VariableDeclarator>> declarations;
};

struct VariableDeclarator {
  std::string identifier;
  unique<Type> type;
  unique<Value> value;
};

struct Assignment : public Statement {
  unique<Reference> target;
  unique<Value> value;
};

struct Return : public Statement {
  unique<Value> value;
};

// Values
struct Value {};

struct PrimitiveValue : public Value {
  /*
   * isInt...
   */
};

struct Int32Value : public PrimitiveValue {
  int32_t value;
};

struct StringValue : public PrimitiveValue {
  std::string value;
};

struct ArrayValue : public PrimitiveValue {
  std::vector<unique<Value>> values;
};

struct Type {};

struct VoidType : public Type {};

struct ArrayType : public Type {
  unique<Type> of;
  size_t length;
  bool dynamic;
};

struct PrimitiveType : public Type {};

struct StringType : public PrimitiveType {};

struct I32Type : public PrimitiveType {};

struct Signature {
  struct Argument {
    unique<Type> type;
    std::string alias;
    std::string identifier;
    unique<Value> value;
  };

  std::string identifier;
  std::vector<Argument> params;
  unique<Type> ret;
  bool variadic;
};
}  // namespace ast
}  // namespace ai
