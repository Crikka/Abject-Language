#pragma once

#include <cstdio>
#include <stack>
#include <string>

namespace ai {

namespace ast {
struct Program;
}  // namespace ast

ast::Program *parse(const std::string &in);
ast::Program *parse_file(const std::string &filename);
}  // namespace ai
