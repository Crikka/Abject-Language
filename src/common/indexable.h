#pragma once

#include <stddef.h>
#include <limits>

namespace ai {
class Indexable {
 private:
  constexpr static size_t undefined = std::numeric_limits<size_t>::max();

 public:
  virtual ~Indexable() = default;

  size_t id() const { return id_; }
  void id(size_t id) { this->id_ = id; }
  bool IsWellDefined() const { return (this->id_ != undefined); }

 protected:
  Indexable() : id_(undefined) {}

 private:
  size_t id_;
};
}  // namespace ai
