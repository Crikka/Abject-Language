#pragma once

namespace ai {
/**
 * The ref countable implementations
 */
template <typename T>
struct cref {
  cref<T>() : intern_(nullptr) {}

  cref<T>(T* intern) : intern_(intern) {
    if (intern_) intern_->ref_count_++;
  }

  cref<T>(const cref<T>& other) : intern_(other.intern_) {
    if (intern_) intern_->ref_count_++;
  }

  ~cref() {
    if (intern_) {
      intern_->ref_count_--;

      if (intern_->ref_count_ == 0) {
        delete intern_;
      }
    }
  }

  T* get() const { return intern_; }

  T* operator->() { return intern_; }

  operator T*() { return get(); }

 private:
  T* intern_;
};
}  // namespace ai
