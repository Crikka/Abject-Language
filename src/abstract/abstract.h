#pragma once

#include "metamodel/cfg/identifier.h"

namespace ai {
class AbstractValue;

class AbstractDomain {
 private:
  struct Operationable {
    void operator<(long value);
    void operator=(long value);

   private:
    AbstractValue *about;
  };

 public:
  Operationable Let(const Identifier &identifier);
};

class AbstractValue {
 public:
  enum Kind { kNumber };

  Kind kind() const { return kind_; }

 private:
  Kind kind_;
};

class AbstractNumber : public AbstractValue {};
}  // namespace ai
