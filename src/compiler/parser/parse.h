#pragma once

#include <cstdio>
#include <stack>
#include <string>

namespace ai {
namespace ast {
struct Program;
}  // namespace ast
}  // namespace ai

namespace ai::parsing {
class Diagnostic;

ast::Program *parse(const std::string &in, Diagnostic *diagnostic = nullptr);
ast::Program *parse_file(const std::string &filename,
                         Diagnostic *diagnostic = nullptr);
}  // namespace ai::parsing
