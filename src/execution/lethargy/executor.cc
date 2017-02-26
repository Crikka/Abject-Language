#include "execution/lethargy/executor.h"

#include "common/memory.h"

#include "metamodel/cfg/code.h"
#include "metamodel/cfg/statements.h"
#include "metamodel/types.h"

#include "execution/lethargy/runtime.h"

#include <vector>

namespace ai {
Executor::Executor() {}

rt::Value *Executor::Start(Code *code, size_t locals_count) {
  rt::Value *result;

  std::vector<rt::Value *> locals(locals_count, nullptr);

  for (const std::unique_ptr<Statement> &statement : code->statements()) {
    switch (statement->kind()) {
      case kStReturn: {
        Return *st_return = statement->As<kStReturn>();

        result = locals[st_return->value()];
        goto end;
      }

      case kStStringLiteral: {
        StringLiteral *st_string = statement->As<kStStringLiteral>();

        size_t left = st_string->var();
        const std::string &right = st_string->value();

        rt::Str *value = new rt::Str();
        value->value = right;

        locals[left] = value;
        break;
      }

      case kStIntegerLiteral: {
        IntegerLiteral *st_integer = statement->As<kStIntegerLiteral>();

        size_t left = st_integer->var();
        int right = st_integer->value();

        rt::Int *value = new rt::Int();
        value->value = right;

        locals[left] = value;
        break;
      }
    }
  }

end:
  return result;
}
}  // namespace ai
