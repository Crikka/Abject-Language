#include "ast.h"

#include <iostream>

namespace abject {
namespace ast {
Program::Program() : Node() {}

void Program::defineModule(std::string name) { this->m_module = name; }

void Program::addChild(Node* node) { m_children.push_back(node); }

void Program::print() {
  if (m_module.empty()) {
    std::cout << "Auto module" << std::endl;
  } else {
    std::cout << "Module : " << m_module << std::endl;
  }

  for (Node* child : m_children) {
    child->print();
  }
}

Empty::Empty() : Node() {}

void Empty::print() { std::cout << "Empty" << std::endl; }

Identifier::Identifier(std::string name) : Node(), m_name(name) {}

void Identifier::print() {
  std::cout << "Identifier <<" << m_name << ">>" << std::endl;
}

VariableDeclaration::VariableDeclaration(Identifier* identifier, Value* value)
    : Node(), m_identifier(identifier), m_value(value) {}

VariableDeclaration::VariableDeclaration(Identifier* identifier)
    : VariableDeclaration(identifier, nullptr) {}

void VariableDeclaration::print() {
  std::cout << "Variable Declaration" << std::endl
            << "  Identifier : ";
  m_identifier->print();
  std::cout << "  Initialized with : ";
  m_value->print();
  std::cout << std::endl;
}

VariablesDeclaration::VariablesDeclaration() : Node() {}

void VariablesDeclaration::push(VariableDeclaration* declaration) {
  m_declarations.push_back(declaration);
}

void VariablesDeclaration::print() {
  std::cout << "Variable Declarations ~~" << std::endl;
  for (VariableDeclaration* declaration : m_declarations) {
    declaration->print();
  }
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

Assignment::Assignment(Identifier* identifier, Value* value)
    : Node(), m_identifier(identifier), m_value(value) {}

void Assignment::print() {
  std::cout << "Assignment" << std::endl
            << "  Left Reference : ";
  m_identifier->print();
  std::cout << "  Right Value : ";
  m_value->print();
  std::cout << std::endl;
}

ArrayLiteral::ArrayLiteral() : Node() {}

void ArrayLiteral::addValues(Value* value) { this->m_values.push_back(value); }

void ArrayLiteral::print() {
  std::cout << "Array Literal" << std::endl;

  for (Value* value : m_values) {
    std::cout << "  ";
    value->print();
  }

  std::cout << std::endl;
}

IntValue::IntValue(int value) : Value(), m_value(value) {}

void IntValue::print() {
  std::cout << "Integer Value (" << m_value << ")" << std::endl;
}

StringValue::StringValue(std::string value) : Value(), m_value(value) {}

void StringValue::print() {
  std::cout << "String Value (" << m_value << ")" << std::endl;
}
Type::Type() : Node() {}

ArrayType::ArrayType(Type* of) : Type(), m_of(of) {}

void ArrayType::print() {
  std::cout << "Array type of ";

  m_of->print();
}

PrimitiveType::PrimitiveType() : Type() {}

StringType::StringType() : PrimitiveType() {}

void StringType::print() { std::cout << "String type" << std::endl; }

TopLevelContent::TopLevelContent() : Node() {}

Define::Define() : TopLevelContent() {}

void Define::print() { std::cout << "Define..." << std::endl; }
}
}
