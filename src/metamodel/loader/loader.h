#pragma once

#include <string>

namespace ai {
class SourceLoader {
 public:
  SourceLoader();

  void LoadRaw(const std::string &source);
  void LoadFile(const std::string &filename);

 private:
};
}  // namespace ai
