#pragma once

#include <atomic>

namespace ai {
struct Countable {
  Countable() : ref_count_(0) {}

 private:
  std::atomic_uint_fast64_t ref_count_;

  template <typename T>
  friend class cref;
};
}  // namespace ai
