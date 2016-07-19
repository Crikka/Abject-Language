#include "metamodel/cfg/cfg.h"

#include "metamodel/cfg/instructions.h"

namespace abject {
CFG::CFG() : entry_(new Block), current_(entry_.get()) {
  entry_->parent = nullptr;
}

CFG::~CFG() {}

void CFG::Push(Instruction *instruction) {
  current_->instructions.emplace_back(instruction);
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
}  // namespace abject
