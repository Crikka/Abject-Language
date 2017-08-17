#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/indexable.h"
#include "common/unique.h"

#include "metamodel/modular.h"

namespace ai {
class Code;
class Model;

class Function : public Indexable {
 public:
  explicit Function(Model *return_type, Code *code,
                    const std::string &name = "");
  virtual ~Function();

  void AddParameter(Model *model, const std::string &name = "");

  const std::vector<std::pair<Model *, std::string>> &parameters() const {
    return parameters_;
  }

  size_t number_of_parameters() const { return parameters_.size(); }
  void locals(size_t locals) { locals_ = locals; }
  size_t locals() const { return locals_; }

  Model *return_type() const;
  Code *code() const;
  const std::string &name() const;

 private:
  std::vector<std::pair<Model *, std::string>> parameters_;
  size_t locals_;
  Model *return_type_;
  unique<Code> code_;
  std::string name_;
};
}  // namespace ai
