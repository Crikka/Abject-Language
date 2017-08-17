#pragma once

#include <cstdint>

namespace ai {
class Identifier {
 public:
  Identifier(uint32_t pos, uint32_t type)
      : data_(static_cast<uint64_t>(pos) << 32 | type) {}

  virtual ~Identifier();

  uint32_t pos() const { return static_cast<uint32_t>(data_ >> 32); }

  uint32_t type() const {
    return static_cast<uint32_t>(data_ & 0x00000000FFFFFFFF);
  }

 private:
  uint64_t data_;
};

}  // namespace ai
