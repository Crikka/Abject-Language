#pragma once

#include "common/countable.h"
#include "common/indexable.h"
#include "common/unique.h"

#include "metamodel/modular.h"

namespace ai {
class Code;

class Function : public Indexable {
 public:
  explicit Function(size_t parameters_accepted, size_t locals_lenght,
                    Code *code);
  virtual ~Function();

  size_t parameters_accepted() const { return parameters_accepted_; }
  size_t locals_length() const { return locals_length_; }
  Code *code() const;

 private:
  size_t parameters_accepted_;
  size_t locals_length_;
  unique<Code> code_;
};
}  // namespace ai
