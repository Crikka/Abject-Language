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

namespace ai::parsing {
template <typename T>
struct ParsingResult {
  bool ok;
  T result;

  ParsingResult() : ok(false) {}
  ParsingResult(T result) : ok(true), result(result) {}

  template <typename S>
  ParsingResult<T> &operator=(const ParsingResult<S> &other) {
    static_assert(std::is_base_of<std::remove_pointer_t<T>,
                                  std::remove_pointer_t<S>>::value,
                  "You can assign only subtype");

    this->ok = other.ok;
    if (other.ok) {
      this->result = other.result;
    }

    return *this;
  }

  template <typename S>
  operator ParsingResult<S>() {
    static_assert(std::is_base_of<std::remove_pointer_t<S>,
                                  std::remove_pointer_t<T>>::value,
                  "You can assign only subtype");

    return ParsingResult<S>(result);
  }

  operator bool() { return ok; }
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
  ParsingResult<ast::Define *> define();
  ParsingResult<ast::Type *> type();
  ParsingResult<ast::Type *> type_namespace();
  ParsingResult<ast::Signature *> signature();
  ast::Code *code();

  // Statements
  ParsingResult<ast::Return *> ret();

  // Values
  ParsingResult<ast::Value *> value();
  ParsingResult<ast::Int32Value *> i32_value();

  StringParsingResult module();
  StringParsingResult literal(const std::string &lit);
  StringParsingResult identifier();
  StringParsingResult alias();

  bool next_is(char c);
  bool forward_if_next_is(char c);
  bool forward_is(char c);
  bool next_is_number();
  bool forward_if_next_is_number();
  bool forward_is_number();

  bool next_is_between(char c1, char c2);
  bool forward_if_next_is_betweek(char c1, char c2);
  bool forward_is_between(char c1, char c2);

  // If "keyword" can be read return true and move forward the cursor
  // otherwise don't move the cursor and return false
  bool keyword(const char *keyword);
  bool skip();

  bool whitespace();
  bool backline();
  bool comment();

  // forward for one character
  char forward();
  void backward();

  template <typename T>
  ParsingResult<T> fail() {
    ParsingResult<T> result;
    result.ok = false;

    return result;
  }

  std::stack<typename std::istream::pos_type> save_points;

  void save();
  void restaure();
  void valid();
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
    skip();

    result->top_level_contents.emplace_back(next_top_level_content.result);

    next_top_level_content = top_level_content();
  }

  return result;
};

ParsingResult<ast::TopLevelContent *> Parser::top_level_content() {
  if (auto result = define()) return result;

  return fail<ast::TopLevelContent *>();
}

ParsingResult<ast::Define *> Parser::define() {
  ParsingResult<ast::Define *> result;

  if (keyword("define")) {
    ParsingResult<ast::Type *> next_type = type_namespace();

    ParsingResult<ast::Signature *> next_signature = signature();
    if (!next_signature.ok) return result;

    if (!forward_if_next_is('{')) return result;

    ast::Code *next_code = code();

    if (!forward_if_next_is('}')) return result;

    ast::Define *define = new ast::Define;

    result.ok = true;
    result.result = define;

    if (next_type) define->on.reset(next_type.result);
    define->signature.reset(next_signature.result);
    define->code.reset(next_code);
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

    if (next_identifier.result == "i32") {
      result_type = new ast::I32Type;
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

/**
 * @brief type_namespace
 * @return
 *
 * Try to parse <type>::
 */
ParsingResult<ast::Type *> Parser::type_namespace() {
  save();

  ParsingResult<ast::Type *> result;

  ParsingResult<ast::Type *> ntype = type();
  if (ntype && literal("::")) {
    valid();

    result = ntype;
  } else {
    restaure();
  }

  return result;
}

ParsingResult<ast::Signature *> Parser::signature() {
  ParsingResult<ast::Signature *> result;

  StringParsingResult next_identifier = identifier();
  if (!next_identifier.ok) return result;

  skip();

  ast::Type *return_type;
  if (forward_if_next_is('#')) {
    ParsingResult<ast::Type *> preturn_type = type();
    if (!preturn_type) return fail<ast::Signature *>();

    return_type = preturn_type.result;
  } else {
    return_type = new ast::VoidType();
  }

  skip();

  std::vector<std::tuple<std::string, std::string, ast::Type *>> list;

  bool fallback = false;

  do {
    if (fallback) {
      // We do a loop without consume anything, try to consume one
      forward();
    }

    fallback = true;

    std::string ralias;
    std::string ridentifier;

    StringParsingResult palias = alias();

    if (palias) {
      skip();

      ralias = palias.result;
    }

    StringParsingResult pidentifier = identifier();

    if (pidentifier) {
      skip();

      ridentifier = pidentifier.result;

      if (forward_if_next_is('#')) {
        ParsingResult<ast::Type *> ptype = type();
        if (!ptype) throw "An argument in not typed";

        list.push_back(std::make_tuple(ralias, ridentifier, ptype.result));

        fallback = false;
      }
    }

    skip();
  } while (!next_is('{'));

  ast::Signature *signature = new ast::Signature;
  signature->identifier = next_identifier.result;
  signature->ret.reset(return_type);

  for (const std::tuple<std::string, std::string, ast::Type *> &l : list) {
    signature->params.emplace_back();

    signature->params.back().type.reset(std::get<2>(l));
    signature->params.back().alias = std::get<0>(l);
    signature->params.back().identifier = std::get<1>(l);
  }

  result.ok = true;
  result.result = signature;

  return result;
}

ast::Code *Parser::code() {
  ast::Code *result = new ast::Code();

loop:
  skip();

  if (ParsingResult<ast::Return *> st = ret()) {
    result->statements.emplace_back(st.result);
    goto loop;
  }

  return result;
}

ParsingResult<ast::Return *> Parser::ret() {
  // save();

  ParsingResult<ast::Return *> result;

  if (keyword("return")) {
    ParsingResult<ast::Value *> next_value = value();
    if (next_value.ok) {
      skip();

      if (forward_if_next_is(';')) {
        //   valid();

        ast::Return *ret = new ast::Return;

        ret->value.reset(next_value.result);

        result.ok = true;
        result.result = ret;
      }
    }
  }

  //  if (!result.ok) restaure();

  return result;
}

ParsingResult<ast::Value *> Parser::value() {
  if (auto result = i32_value()) return result;

  return fail<ast::Value *>();
}

ParsingResult<ast::Int32Value *> Parser::i32_value() {
  std::string following;

  while (next_is_number()) {
    following += forward();
  }

  if (following.empty()) return fail<ast::Int32Value *>();

  ast::Int32Value *val = new ast::Int32Value;

  val->value = std::stoi(following);

  return val;
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

/**
 * @brief alias
 * @return
 *
 * An identifier directli followed by ":"
 */
StringParsingResult Parser::alias() {
  save();

  StringParsingResult result = fail<std::string>();

  StringParsingResult pidentifier = identifier();
  if (pidentifier && forward_if_next_is(':')) {
    valid();

    result = pidentifier;
  } else {
    restaure();
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

bool Parser::next_is_number() {
  bool result = next_is_between('0', '9');

  return result;
}

bool Parser::forward_if_next_is_number() {
  bool result = next_is_number();

  if (result) forward();

  return result;
}

bool Parser::forward_is_number() {
  bool result = next_is_between('0', '9');

  if (!is->eof()) is->get();

  return result;
}

bool Parser::next_is_between(char c1, char c2) {
  if (is->eof()) return false;

  char c = is->peek();

  return ((c >= c1) && (c <= c2));
}

bool Parser::forward_if_next_is_betweek(char c1, char c2) {
  bool result = next_is_between(c1, c2);

  if (result) forward();

  return result;
}

bool Parser::forward_is_between(char c1, char c2) {
  if (is->eof()) return false;

  char c = is->get();

  return ((c >= c1) && (c <= c2));
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

char Parser::forward() { return is->get(); }

void Parser::backward() { is->unget(); }

void Parser::save() { save_points.push(is->tellg()); }

void Parser::restaure() {
  assert(!save_points.empty());

  is->seekg(save_points.top());
  save_points.pop();
}

void Parser::valid() {
  assert(!save_points.empty());

  save_points.pop();
}
}  // namespace ai::parsing
