#pragma once

#include <cstdint>

namespace ai {
void MurmurHash3_x86_32(const void* key, int len, uint32_t seed, uint32_t* out);
void MurmurHash3_x86_128(const void* key, int len, uint32_t seed, uint32_t* out);
void MurmurHash3_x64_128(const void* key, int len, uint32_t seed, uint64_t* out);
}  // namespace ai
