#pragma once

#include <cstdio>
#include <stack>
#include <string>

#include "tanuki/tanuki.h"

namespace ai {
void parse(tanuki::String in);
void parseFile(std::string fileName);
}  // namespace ai
