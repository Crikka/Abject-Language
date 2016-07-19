#pragma once

#include "tools/countable.h"
#include "tools/cref.h"

#include <memory>
#include <vector>

namespace abject {
struct Instruction;

class CFG : public Countable {
 private:
  struct Block : public Countable {
    Block *parent;
    std::vector<cref<Block>> children;

    std::vector<std::unique_ptr<Instruction>> instructions;
  };

 public:
  CFG();
  virtual ~CFG();

  void Push(Instruction *instruction);
  void Branch();
  void Trunk();

 private:
  std::unique_ptr<Block> entry_;
  Block *current_;
};

}  // namespace abject
