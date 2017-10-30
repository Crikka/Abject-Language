#pragma once

#include <cstdio>
#include <stack>
#include <string>

namespace ai {
class Diagnostic;

namespace ast {
struct Program;
}  // namespace ast

ast::Program *parse(const std::string &in, Diagnostic *diagnostic = nullptr);
ast::Program *parse_file(const std::string &filename, Diagnostic *diagnostic = nullptr);
}  // namespace ai
