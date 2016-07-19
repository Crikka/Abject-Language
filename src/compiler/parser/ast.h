#pragma once

#include <string>
#include <vector>

namespace abject {
namespace ast {
class Node;
class Program;
class Empty;
class Identifier;
class VariablesDeclaration;
class VariableDeclaration;
class Assignment;
class ArrayLiteral;
class Value;
class IntValue;
class StringValue;

// Type
class Type;
class ArrayType;
class PrimitiveType;
class StringType;

class Node {
 public:
  virtual ~Node() = default;

  virtual void print() = 0;
};

class Program : public Node {
 public:
  Program();
  void defineModule(std::string name);
  void addChild(Node* node);
  void print() override;

 private:
  std::string m_module;
  std::vector<Node*> m_children;
};

class Empty : public Node {
 public:
  Empty();
  void print() override;
};

class Identifier : public Node {
 public:
  Identifier(std::string name);
  void print() override;

 private:
  std::string m_name;
};

class VariableDeclaration : public Node {
 public:
  VariableDeclaration(Identifier* identifier, Value* value);
  VariableDeclaration(Identifier* identifier);
  void print() override;

 private:
  Identifier* m_identifier;
  Value* m_value;
};

class VariablesDeclaration : public Node {
 public:
  VariablesDeclaration();
  void push(VariableDeclaration* declaration);
  void print() override;

 private:
  std::vector<VariableDeclaration*> m_declarations;
};

class Assignment : public Node {
 public:
  Assignment(Identifier* identifier, Value* value);
  void print() override;

 private:
  Identifier* m_identifier;
  Value* m_value;
};

class ArrayLiteral : public Node {
 public:
  ArrayLiteral();
  void addValues(Value* value);
  void print() override;

 private:
  std::vector<Value*> m_values;
};

class Value : public Node {
 public:
  /*
   * isInt...
   */
};

class IntValue : public Value {
 public:
  IntValue(int value);
  void print() override;

 private:
  int m_value;
};

class StringValue : public Value {
 public:
  StringValue(std::string value);
  void print() override;

 private:
  std::string m_value;
};

class Type : public Node {
 public:
  Type();
};

class ArrayType : public Type {
 public:
  ArrayType(Type* of);

  void print() override;

 private:
  Type* m_of;
};

class PrimitiveType : public Type {
 public:
  PrimitiveType();
};

class StringType : public PrimitiveType {
 public:
  StringType();

  void print() override;
};

class TopLevelContent : public Node {
 public:
  TopLevelContent();
};

class Define : public TopLevelContent {
 public:
  Define();

  void print() override;
};
}
}
