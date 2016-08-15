#include "execution/lethargy/memory.h"

#include <cstdlib>

namespace ai {
Memory::Memory(size_t length)
    : length_(length),
      current_(0),
      data_((void **)malloc(length * sizeof(void *))) {}

Memory::~Memory() { free(data_); }

MemoryView Memory::View(size_t length) {
  if (current_ + length < length_) {
    MemoryView result(data_ + current_);
    current_ += length;

    return result;
  }

  throw "Cannot allocate";
}

MemoryView::MemoryView(void **data) : data_(data) {}

}  // namespace ai
