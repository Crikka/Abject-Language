#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>

#include <functional>
#include <iostream>

namespace ai {
class MemoryView;

class Memory {
  static_assert(sizeof(char) == 1, "Just to be sure");

 public:
  explicit Memory(size_t length);
  virtual ~Memory();

  MemoryView View();

 private:
  char *data_;
};

class MemoryView {
 public:
  // Not explicit
  MemoryView(char *data);
  MemoryView(const MemoryView &other);

  template <typename T>
  T Get(size_t n) const {
    return reinterpret_cast<T>(data_ + n);
  }

  void Set(size_t n, const void *something, size_t length) {
    memcpy(data_ + n, something, length);
  }

#define MemoryViewAutoSet(type) \
  void Set(size_t n, type something) { Set(n, &something, sizeof(type)); }

  MemoryViewAutoSet(int);
  MemoryViewAutoSet(long);
  MemoryViewAutoSet(char);

#undef MemoryViewAutoSet

 private:
  char *data_;
};

struct ArrayOfPointer {
  template <typename T>
  T *Get(size_t n) const {
    return mview_.Get<T *>(n * ps);
  }

  void Set(size_t n, const void *something) {
    mview_.Set(n * ps, something, ps);
  }

  explicit ArrayOfPointer(MemoryView mview) : mview_(mview) {}

 private:
  MemoryView mview_;
  static constexpr size_t ps = sizeof(void *);
};
}  // namespace ai
