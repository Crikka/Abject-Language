#pragma once

#include <memory>
#include <tuple>
#include <utility>
#include <vector>

#include "common/indexable.h"
#include "common/unique.h"

namespace ai {
struct Statement;

class Block : public Indexable {
 public:
  Block();
  virtual ~Block();

  void Push(Statement *statement);
  const std::vector<unique<Statement>> &statements() const;

 private:
  std::vector<unique<Statement>> statements_;
};

class Code {
 public:
  Code();
  virtual ~Code();

  struct BlockGraph {
    size_t from;
    size_t val;
    size_t consequent;
    size_t alternate;
  };

  Block *EntryBlock() const;
  size_t number_of_blocks() const;
  const std::vector<unique<Block>> &blocks() const;
  const std::vector<BlockGraph> &block_graph() const;

  /**
   * @brief Branch
   * @param from
   * @param val
   * @return
   *
   * Create a block if val is true and a block is val is false
   * return it respectively in a pair
   */
  std::pair<Block *, Block *> Branch(Block *from, size_t val);

  /**
   * @brief Branch
   * @param from
   * @param val
   * @param alternate
   * @return
   *
   * Create a block if val is true, otherwise branch to alternate
   * Return the created consequent branch
   */
  Block *Branch(Block *from, size_t val, Block *alternate);

  /**
   * @brief Branch
   * @param from
   * @param val
   * @param consequent
   * @param alternate
   *
   * Branch val to two existing block
   */
  void Branch(Block *from, size_t val, Block *consequent, Block *alternate);

 private:
  Block *create_block();

  std::vector<unique<Block>> blocks_;
  // from, val, consequent, alternate
  std::vector<BlockGraph> block_graph_;
};
}  // namespace ai
