#include "parse.h"

#include <fstream>
#include <iostream>

#include "ast.h"

namespace abject {
/* -- Tokens -- */
static tanuki::ref<tanuki::Fragment<ast::Program>> TokenMain();

/* Top Level */
static tanuki::ref<tanuki::Fragment<ast::TopLevelContent>> TokenTop();

static tanuki::ref<tanuki::Fragment<ast::Define>> TokenDefine();
/* --------- */

/* -- Type -- */
static tanuki::ref<tanuki::Fragment<ast::Type>> TokenType();
static tanuki::ref<tanuki::Fragment<ast::Type>> TokenAtomicType();

static tanuki::ref<tanuki::Fragment<ast::StringType>> TokenStringType();
/* ---------- */

/* -- Value -- */
static tanuki::ref<tanuki::Fragment<ast::Value>> TokenValue();

static tanuki::ref<tanuki::Fragment<ast::IntValue>> TokenIntValue();
static tanuki::ref<tanuki::Fragment<ast::StringValue>> TokenStringValue();
/* ----------- */

/* ------------ */

template <typename TToken>
static void skip(TToken token) {
  use_tanuki;

  token->skip(blank());
  token->skip(lineTerminator());
  token->skip(range(constant("/*"), constant("*/")));
  token->skip(range(constant("//"), lineTerminator()));
}

void parse(tanuki::String in) {
  if (tanuki::ref<ast::Program> result = TokenMain()->match(in)) {
    result->print();
  } else {
    std::cout << "Parsing fail" << std::endl;
  }
}

void parseFile(std::string fileName) {
  std::ifstream ifs(fileName);
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      (std::istreambuf_iterator<char>()));

  parse(content.c_str());
}

static auto identifier = tanuki::word(tanuki::letter());

tanuki::ref<tanuki::Fragment<ast::Program>> TokenMain() {
  using namespace ast;
  use_tanuki;

  ref<Fragment<Program>> result = fragment<Program>();
  result->skipAtEnd = true;
  skip(result);

  result->handle(
      [](auto, ref<std::string> module, auto) -> ref<Program> {
        ref<Program> result(new Program());
        result->defineModule(*dereference(module));

        return result;
      },
      constant("module "), identifier, TokenTop());

  return result;
}

/* Top Level */
tanuki::ref<tanuki::Fragment<ast::TopLevelContent>> TokenTop() {
  using namespace ast;
  use_tanuki;

  return Fragment<TopLevelContent>::select(TokenDefine());
}

tanuki::ref<tanuki::Fragment<ast::Define>> TokenDefine() {
  using namespace ast;
  use_tanuki;

  ref<Fragment<Define>> result = fragment<Define>();
  skip(result);

  result->handle([](auto, auto, auto, auto, auto, auto, auto,
                    auto) -> ref<Define> { return new Define(); },
                 constant("define "), TokenType(), constant("::"), identifier,
                 constant('('), constant(')'), constant('{'), constant('}'));

  return result;
}

/* --------- */

/* -- Type -- */
tanuki::ref<tanuki::Fragment<ast::Type>> TokenType() {
  using namespace ast;
  use_tanuki;

  ref<Fragment<Type>> result = fragment<Type>();
  result->handle([](ref<Type> in) -> ref<Type> { return in; },
                 TokenAtomicType());
  result->handle([](auto in, auto,
                    auto) -> ref<Type> { return new ArrayType(in.release()); },
                 result, constant('['), constant(']'));

  return result;
}

tanuki::ref<tanuki::Fragment<ast::Type>> TokenAtomicType() {
  using namespace ast;
  use_tanuki;

  return Fragment<Type>::select(TokenStringType());
}

tanuki::ref<tanuki::Fragment<ast::StringType>> TokenStringType() {
  using namespace ast;
  use_tanuki;

  ref<Fragment<StringType>> result = fragment<StringType>();
  result->handle([](auto) -> ref<StringType> { return new StringType(); },
                 constant("String"));

  return result;
}

/* -- Value -- */
tanuki::ref<tanuki::Fragment<ast::Value>> TokenValue() {
  using namespace ast;
  use_tanuki;

  return Fragment<Value>::select(TokenIntValue(), TokenStringValue());
}

tanuki::ref<tanuki::Fragment<ast::IntValue>> TokenIntValue() {
  using namespace ast;
  use_tanuki;

  ref<Fragment<IntValue>> result = fragment<IntValue>();
  result->handle([](ref<int> value) -> ref<IntValue> { return new IntValue(*dereference(value)); },
                 integer());

  return result;
}

static tanuki::ref<tanuki::Fragment<ast::StringValue>> TokenStringValue() {
  using namespace ast;
  use_tanuki;

  ref<Fragment<StringValue>> result = fragment<StringValue>();
  result->handle([](auto, ref<std::string> value, auto) -> ref<StringValue> { return new StringValue(*dereference(value)); },
                 constant('"'), word(letter() or anyOf(' ', '\'')), constant('"'));

  return result;
}
/* ----------- */

/* ---------- */
}
