#pragma once

#include <stdint.h>

namespace abject {
struct Identifier {
  Identifier(uint32_t pos, uint32_t method)
      : data_((uint64_t)pos << 32 | method) {}

  virtual ~Identifier() {}

  uint32_t pos() const { return (uint32_t)(data_ >> 32); }
  uint32_t method() const { return (uint32_t)(data_ & 0x00000000FFFFFFFF); }

 private:
  uint64_t data_;
};

}  // namespace abject
