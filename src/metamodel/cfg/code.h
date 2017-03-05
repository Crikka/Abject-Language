#pragma once

#include "common/cref.h"
#include "common/unique.h"

#include <memory>
#include <vector>

namespace ai {
struct Statement;

class Code {
 public:
  Code();
  virtual ~Code();

  void Push(Statement *statement);

  const std::vector<unique<Statement>> &statements() const {
    return statements_;
  }

 private:
  std::vector<unique<Statement>> statements_;
};
}  // namespace ai
