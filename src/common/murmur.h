#pragma once

#include <cstdint>

namespace ai {
uint32_t murmur(const char *key, uint32_t len, uint32_t seed);
}  // namespace ai
