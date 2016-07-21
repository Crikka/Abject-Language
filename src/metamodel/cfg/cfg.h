#pragma once

#include "tools/countable.h"
#include "tools/cref.h"

#include <memory>
#include <vector>

namespace abject {
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

 private:
  std::unique_ptr<Block> entry_;
  Block *current_;
};

}  // namespace abject
