#include "abstract/abstract.h"

#include <iostream>

namespace ai {
AbstractDomain::Operationable AbstractDomain::Let(
    const Identifier &identifier) {
  return Operationable();
}

void AbstractDomain::Operationable::operator<(long value) {
  std::cout << "Hello " << value << std::endl;
}

void AbstractDomain::Operationable::operator=(long value) {
  std::cout << "world " << value << std::endl;
}
}  // namespace ai
