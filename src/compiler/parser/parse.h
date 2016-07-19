#pragma once

#include <stack>
#include <string>
#include <cstdio>

#include "tanuki/tanuki.h"

namespace abject {
void parse(tanuki::String in);
void parseFile(std::string fileName);
}
