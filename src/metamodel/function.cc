#include "metamodel/function.h"

#include "metamodel/types.h"

#include "metamodel/cfg/code.h"

namespace ai {

Function::Function(Model *return_type, Code *code, const std::string &name)
    : parameters_(0),
      locals_(0),
      return_type_(return_type),
      code_(code),
      name_(name) {}

Function::~Function() {}

void Function::AddParameter(Model *model, const std::string &name) {
  parameters_.push_back(std::make_pair(model, name));
}

Model *Function::return_type() const { return return_type_; }

Code *Function::code() const { return code_.get(); }

const std::string &Function::name() const { return name_; }

}  // namespace ai
