#include "compiler/parser/parse.h"

#include <fstream>
#include <iostream>

#include <cassert>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stack>

#include "compiler/parser/ast.h"

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

  Parser(std::istream *is) : is(is) {}

  StringParsingResult module();
  StringParsingResult literal(const std::string &str);
  StringParsingResult identifier();

  bool next_is(char c);
  bool forward_if_next_is(char c);
  bool forward_is(char c);
  // If "keyword" can be read return true and move forward the cursor
  // otherwise don't move the cursor and return false
  bool keyword(const char *keyword);
  bool separator();

  bool whitespace();
  bool backline();
  bool comment();

  // forward for one character
  void forward();
  void backward();
};

ast::Program *parse_from_stream(std::istream *is) {
  ast::Program *result = new ast::Program;

  Parser parser(is);
  while (parser.separator())
    ;
  parser.module();
  while (parser.separator())
    ;
  // result->defineModule(parser.module());

  return result;
}

ast::Program *parse(const std::string &in) {
  std::istringstream is(in);

  return parse_from_stream(&is);
}

ast::Program *parse_file(const std::string &filename) {
  std::ifstream is(filename);

  return parse_from_stream(&is);
}

StringParsingResult Parser::module() {
  pos_t pos = is->tellg();

  StringParsingResult result;

  if (keyword("module")) {
    std::cerr << "parsing module" << std::endl;

    if (separator()) {
      StringParsingResult id = identifier();
      if (id.ok) {
        std::cerr << "module : " << id.result << std::endl;
      }
    }
  }

  return result;
}

StringParsingResult Parser::literal(const std::string &str) {}

StringParsingResult Parser::identifier() {
  StringParsingResult result;
  int32_t c = is->peek();

  if (std::isalpha(c) || c == '$') {
    result.ok = true;
    int32_t c = is->get();

    while (std::isalnum(c) || c == '$') {
      result.result += c;
      if (is->eof()) break;

      c = is->get();
    }
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
  // If keyword ask is "empty" return false...
  if (keyword[0] == '\0') return false;

  bool result = false;

  size_t i = 0;
  char c = keyword[i];
  while (forward_if_next_is(c)) {
    i++;
    c = keyword[i];

    if (c == '\0') {
      result = true;
      break;
    }
  }

  return result;
}

bool Parser::separator() {
  bool result = false;

  while (whitespace() || comment()) {
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
}
