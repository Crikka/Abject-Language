#include "metamodel/function.h"

#include "metamodel/cfg/code.h"

namespace ai {

Function::Function(Code *code) : parameters_(0), locals_(0), code_(code) {}

Function::~Function() {}

Code *Function::code() const { return code_.get(); }
}  // namespace ai
