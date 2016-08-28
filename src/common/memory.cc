#include "common/memory.h"

#include <cstdlib>

namespace ai {
Memory::Memory(size_t length) : data_(new char[length]) {}

Memory::~Memory() { delete[] data_; }

MemoryView Memory::View() { return data_; }

MemoryView::MemoryView(char* data) : data_(data) {}

MemoryView::MemoryView(const MemoryView& other) : data_(other.data_) {}
}  // namespace ai
