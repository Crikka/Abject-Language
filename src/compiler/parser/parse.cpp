#include "compiler/parser/parse.h"

#include <fstream>
#include <iostream>

#include <cassert>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stack>

#include "compiler/parser/ast.h"
#include "compiler/parser/diagnostic.h"

namespace ai {
template <typename T>
struct ParsingResult {
  bool ok = false;
  T result;
};

typedef ParsingResult<std::string> StringParsingResult;

struct Parser {
  typedef std::istream::pos_type pos_t;

  std::istream *is;
  Diagnostic *diagnostic;

  explicit Parser(std::istream *is, Diagnostic *diagnostic)
      : is(is), diagnostic(diagnostic) {}

  ast::Program *TryToParse();

  ParsingResult<ast::TopLevelContent *> top_level_content();
  ParsingResult<ast::Type *> type();
  ParsingResult<ast::Signature *> signature();
  StringParsingResult module();
  StringParsingResult literal(const std::string &lit);
  StringParsingResult identifier();

  bool next_is(char c);
  bool forward_if_next_is(char c);
  bool forward_is(char c);
  // If "keyword" can be read return true and move forward the cursor
  // otherwise don't move the cursor and return false
  bool keyword(const char *keyword);
  bool skip();

  bool whitespace();
  bool backline();
  bool comment();

  // forward for one character
  void forward();
  void backward();
};

ast::Program *parse_from_stream(std::istream *is, Diagnostic *diagnostic) {
  Parser parser(is, diagnostic);

  return parser.TryToParse();
}

ast::Program *parse(const std::string &in, Diagnostic *diagnostic) {
  std::istringstream is(in);

  return parse_from_stream(&is, diagnostic);
}

ast::Program *parse_file(const std::string &filename, Diagnostic *diagnostic) {
  std::ifstream is(filename);

  return parse_from_stream(&is, diagnostic);
}

StringParsingResult Parser::module() {
  StringParsingResult result;

  if (keyword("module")) {
    result = identifier();
  }

  return result;
}

ast::Program *Parser::TryToParse() {
  ast::Program *result = new ast::Program;

  skip();

  StringParsingResult next_module = module();
  if (next_module.ok) {
    result->module = next_module.result;
  }

  skip();

  ParsingResult<ast::TopLevelContent *> next_top_level_content =
      top_level_content();
  while (next_top_level_content.ok) {
    result->top_level_contents.emplace_back(next_top_level_content.result);

    next_top_level_content = top_level_content();
  }

  return result;
};

ParsingResult<ast::TopLevelContent *> Parser::top_level_content() {
  ParsingResult<ast::TopLevelContent *> result;

  if (keyword("define")) {
    ast::Define *define = new ast::Define;

    result.ok = true;
    result.result = define;

    ParsingResult<ast::Type *> next_type = type();
    if (next_type.ok) define->on.reset(next_type.result);

    StringParsingResult quad_collon = literal("::");

    ParsingResult<ast::Signature *> next_signature = signature();
    if (next_signature.ok) define->signature.reset(next_signature.result);

    skip();
    forward_if_next_is('{');
    skip();
    forward_if_next_is('}');
    skip();
  }

  return result;
}

ParsingResult<ast::Type *> Parser::type() {
  ParsingResult<ast::Type *> result;

  ast::Type *result_type = nullptr;

  StringParsingResult next_identifier = identifier();
  if (next_identifier.ok) {
    if (next_identifier.result == "String") {
      result_type = new ast::StringType;
    }
  }

  if (result_type) {
    while (next_is('[')) {
      forward();

      // parse digit...

      if (forward_if_next_is(']')) {
        ast::ArrayType *array = new ast::ArrayType;
        array->of.reset(result_type);
        array->dynamic = true;

        result_type = array;
      }
    }
  }

  if (result_type) {
    result.ok = true;
    result.result = result_type;
  }

  return result;
}

ParsingResult<ast::Signature *> Parser::signature() {
  ParsingResult<ast::Signature *> result;

  StringParsingResult next_identifier = identifier();
  if (!next_identifier.ok) return result;

  std::cerr << ">> " << next_identifier.result << std::endl;

  skip();

  if (!forward_if_next_is('(')) return result;

  std::cerr << "b1" << std::endl;

  skip();

  bool guess;

  std::vector<std::tuple<std::string, ast::Type *>> list;

  do {
    guess = false;

    StringParsingResult next_identifier = identifier();

    if (next_identifier.ok) {
      skip();

      if (forward_if_next_is(':')) {
        skip();

        ParsingResult<ast::Type *> next_type = type();
        if (next_type.ok) {
          list.push_back(
              std::make_tuple(next_identifier.result, next_type.result));

          skip();

          if (forward_if_next_is(',')) {
            skip();

            guess = true;
          }
        }
      }
    }
  } while (guess);

  if (forward_if_next_is(')')) {
    ast::Signature *signature = new ast::Signature;
    signature->name = next_identifier.result;

    for (const std::tuple<std::string, ast::Type *> &l : list) {
      signature->params.emplace_back();

      std::get<0>(signature->params.back()).reset(std::get<1>(l));
      std::get<1>(signature->params.back()) = std::get<0>(l);
    }

    result.ok = true;
    result.result = signature;
  }

  return result;
}

StringParsingResult Parser::literal(const std::string &lit) {
  StringParsingResult result;

  size_t length = lit.size();

  // If keyword ask is "empty" return false...
  if (length == 0) return result;

  result.ok = true;
  result.result = lit;

  for (size_t i = 0; i < length; i++) {
    char c = lit[i];

    if (!forward_if_next_is(c)) {
      result.ok = false;
      break;
    }
  }

  return result;
}

StringParsingResult Parser::identifier() {
  StringParsingResult result;
  int32_t c = is->peek();

  if (std::isalpha(c) || c == '$') {
    result.ok = true;

    do {
      c = is->get();

      result.result += c;
      if (is->eof()) break;

      c = is->peek();
    } while (std::isalnum(c) || c == '$');
  }

  return result;
}

bool Parser::next_is(char c) {
  if (is->eof()) return false;

  return (is->peek() == c);
}

bool Parser::forward_if_next_is(char c) {
  bool result = next_is(c);

  if (result) forward();

  return result;
}

bool Parser::forward_is(char c) {
  if (is->eof()) return false;

  return (is->get() == c);
}

bool Parser::keyword(const char *keyword) {
  bool result = false;

  StringParsingResult next_literal = literal(keyword);

  if (next_literal.ok) {
    // a keyword have to be followed by a separator!
    result = skip();
  }

  return result;
}

bool Parser::skip() {
  bool result = false;

  while (!is->eof() && (whitespace() || comment())) {
    result = true;
  }

  return result;
}

bool Parser::whitespace() {
  bool result = false;

  if (forward_if_next_is(' ')) {
    result = true;
  } else if (forward_if_next_is('\t')) {
    result = true;
  } else if (backline()) {
    result = true;
  }

  return result;
}

bool Parser::backline() {
  bool result = false;

  if (is->eof()) {
    result = true;
  } else if (forward_if_next_is('\n')) {
    result = true;
  } else if (forward_if_next_is('\r')) {
    if (forward_if_next_is('\n')) {
      result = true;
    } else {
      backward();
    }
  }

  return result;
}

bool Parser::comment() {
  bool result = false;

  if (forward_if_next_is('/')) {
    if (forward_if_next_is('/')) {
      result = true;
      while (!backline()) {
        forward();
      }
    } else if (forward_if_next_is('*')) {
      result = true;
      bool loop = true;

      while (loop) {
        if (is->eof()) {
          loop = false;
        } else {
          if (forward_is('*')) {
            if (forward_is('/')) {
              loop = false;
            }
          }
        }
      }
    }
  }

  return result;
}

void Parser::forward() { is->get(); }

void Parser::backward() { is->unget(); }
}  // namespace ai
