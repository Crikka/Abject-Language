#pragma once

#include <memory>

namespace ai {
template <typename T>
using unique = std::unique_ptr<T>;
}  // namespace ai
