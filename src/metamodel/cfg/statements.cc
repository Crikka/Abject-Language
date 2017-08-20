#include "metamodel/cfg/statements.h"

namespace ai {
void Visitor::Visit(Statement *statement) { statement->visit(this); }
}  // namespace ai
