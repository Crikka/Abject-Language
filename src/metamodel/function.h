#pragma once

#include "common/countable.h"
#include "common/indexable.h"
#include "common/unique.h"

#include "metamodel/modular.h"

namespace ai {
class Code;

class Function : public Indexable {
 public:
  explicit Function(Code *code);
  virtual ~Function();

  size_t parameters() const { return parameters_; }
  void parameters(size_t parameters) { parameters_ = parameters; }
  void locals(size_t locals) { locals_ = locals; }
  size_t locals() const { return locals_; }

  Code *code() const;

 private:
  size_t parameters_;
  size_t locals_;
  unique<Code> code_;
};
}  // namespace ai
