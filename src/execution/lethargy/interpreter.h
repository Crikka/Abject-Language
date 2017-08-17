#pragma once

namespace ai {
class Metamodel;
class Module;

class Interpreter {
 public:
  explicit Interpreter(Metamodel *metamodel);

  void Start(Module *module);

 private:
  Metamodel *metamodel_;
};
}  // namespace ai
