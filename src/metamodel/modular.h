#pragma once

namespace ai {
class Module;

struct Modular {
 public:
  Modular(Module *module);
  virtual ~Modular();

  Module *module() const;

 private:
  Module *module_;
};
}  // namespace ai
