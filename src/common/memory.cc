#include "common/memory.h"

#include <cstdlib>

namespace ai {
Memory::Memory(size_t length) : data_(new char[length]) {}

Memory::~Memory() { delete[] data_; }

MemoryView Memory::View() { return MemoryView(data_); }

MemoryView::MemoryView(char *data) : data_(data) {}
}  // namespace ai
