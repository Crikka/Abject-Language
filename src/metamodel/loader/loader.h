#pragma once

#include "common/countable.h"

#include <string>

namespace ai {
class SourceLoader : public Countable {
public:
  SourceLoader();

  void LoadRaw(const std::string &source);
  void LoadFile(const std::string &filename);

private:

};
}  // namespace ai
