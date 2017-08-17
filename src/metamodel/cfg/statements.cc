#include "metamodel/cfg/statements.h"

namespace ai {
void Visitor::Visit(Statement *statement) { statement->visit(this); }

Block::Block() : Statement() {}

void Block::AddStatement(Statement *statement) {
  statements_.emplace_back(statement);
}

const std::vector<std::unique_ptr<Statement>> &Block::statements() const {
  return statements_;
}
}  // namespace ai
