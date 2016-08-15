#pragma once

#include "common/countable.h"
#include "common/cref.h"

#include <memory>
#include <vector>

namespace ai {
struct Statement;

class CFG : public Countable {
 private:
  struct Block : public Countable {
    Block *parent;
    std::vector<cref<Block>> children;

    std::vector<std::unique_ptr<Statement>> statements;
  };

 public:
  CFG();
  virtual ~CFG();

  void Push(Statement *statement);
  void Branch();
  void Trunk();

  Block *entry() const { return entry_.get(); }

 private:
  std::unique_ptr<Block> entry_;
  Block *current_;
};

}  // namespace ai
