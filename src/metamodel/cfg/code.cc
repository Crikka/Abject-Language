#include "metamodel/cfg/code.h"

#include "metamodel/cfg/statements.h"

namespace ai {
Code::Code() {}

Code::~Code() {}

void Code::Push(Statement *statement) { statements_.emplace_back(statement); }
}  // namespace ai
