#include "metamodel/cfg/code.h"

#include "metamodel/cfg/statements.h"

namespace ai {
Block::Block() {}

Block::~Block() {}

void Block::Push(Statement *statement) { statements_.emplace_back(statement); }

const std::vector<unique<Statement>> &Block::statements() const {
  return statements_;
}

Code::Code() {
  // Entry block
  create_block();
}

Code::~Code() {}

Block *Code::EntryBlock() const { return blocks_[0].get(); }

size_t Code::number_of_blocks() const { return blocks_.size(); }

const std::vector<unique<Block>> &Code::blocks() const { return blocks_; }

const std::vector<Code::BlockGraph> &Code::block_graph() const {
  return block_graph_;
}

std::pair<Block *, Block *> Code::Branch(Block *from, size_t val) {
  Block *consequent = create_block();
  Block *alternate = create_block();

  block_graph_.push_back({from->id(), val, consequent->id(), alternate->id()});

  return std::make_pair(consequent, alternate);
}

Block *Code::Branch(Block *from, size_t val, Block *alternate) {
  Block *consequent = create_block();

  block_graph_.push_back({from->id(), val, consequent->id(), alternate->id()});

  return consequent;
}

void Code::Branch(Block *from, size_t val, Block *consequent,
                  Block *alternate) {
  block_graph_.push_back({from->id(), val, consequent->id(), alternate->id()});
}

Block *Code::create_block() {
  Block *result = new Block;
  result->id(blocks_.size());

  blocks_.emplace_back(result);

  return result;
}
}  // namespace ai
