#include "metamodel/cfg/cfg.h"

#include "metamodel/cfg/statements.h"

namespace ai {
CFG::CFG() : entry_(new Block), current_(entry_.get()) {
  entry_->parent = nullptr;
}

CFG::~CFG() {}

void CFG::Push(Statement *statement) {
  current_->statements.emplace_back(statement);
}

void CFG::Branch() {
  Block *child = new Block();
  child->parent = current_;
  current_->children.push_back(child);

  current_ = child;
}

void CFG::Trunk() {
  if (current_->parent) {
    current_ = current_->parent;
  }
}
}  // namespace ai
