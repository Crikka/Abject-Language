#pragma once

#include "common/countable.h"
#include "common/cref.h"

#include <cstddef>

namespace ai {
class MemoryView;

class Memory {
 public:
  explicit Memory(size_t length);
  virtual ~Memory();

  MemoryView View(size_t length);

 private:
  size_t length_;
  size_t current_;
  void **data_;
};

class MemoryView {
 public:
  explicit MemoryView(void **data);

  template <typename T>
  T *Get(size_t n) const {
    return reinterpret_cast<T *>(data_[n]);
  }

  void Set(size_t n, void *something) { data_[n] = something; }

 private:
  void **data_;
};
}  // namespace ai
