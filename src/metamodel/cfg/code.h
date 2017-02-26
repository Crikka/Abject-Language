#pragma once

#include "common/countable.h"
#include "common/cref.h"

#include <memory>
#include <vector>

namespace ai {
struct Statement;

class Code : public Countable {
 public:
  Code();
  virtual ~Code();

  void Push(Statement *statement);

  const std::vector<std::unique_ptr<Statement>> &statements() const {
    return statements_;
  }

 private:
  std::vector<std::unique_ptr<Statement>> statements_;
};
}  // namespace ai
