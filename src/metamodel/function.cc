#include "metamodel/function.h"

#include "metamodel/cfg/code.h"

namespace ai {

Function::Function(size_t parameters_accepted, size_t locals_lenght, Code *code)
    : parameters_accepted_(parameters_accepted),
      locals_length_(locals_lenght),
      code_(code) {}

Function::~Function() {}

Code *Function::code() const { return code_.get(); }
}  // namespace ai
