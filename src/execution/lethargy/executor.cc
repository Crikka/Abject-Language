#include "execution/lethargy/executor.h"

#include <vector>

#include "common/memory.h"

#include "metamodel/cfg/code.h"
#include "metamodel/cfg/statements.h"
#include "metamodel/function.h"
#include "metamodel/metamodel.h"
#include "metamodel/types.h"

#include "execution/lethargy/runtime.h"

namespace ai {
struct Executor::Impl {
  Metamodel *metamodel;

  rt::Value *Call(size_t function_id, const std::vector<rt::Value *> &args);
  rt::Value *Eval(Code *code, std::vector<rt::Value *> &&locals);
};

Executor::Executor(Metamodel *metamodel) : impl(new Impl) {
  impl->metamodel = metamodel;
}

Executor::~Executor() {}

rt::Value *Executor::Start(size_t function_id,
                           const std::vector<rt::Value *> args) {
  return impl->Call(function_id, args);
}

rt::Value *Executor::Impl::Call(size_t function_id,
                                const std::vector<rt::Value *> &args) {
  Function *fct = metamodel->function(function_id);

  size_t parameter_accepted = fct->parameters_accepted();
  size_t locals_length = fct->locals_length();
  Code *code = fct->code();

  assert(args.size() == parameter_accepted);
  assert(locals_length >= parameter_accepted);

  std::vector<rt::Value *> locals(locals_length, nullptr);
  for (size_t i = 0; i < parameter_accepted; i++) {
    locals[i] = args[i];
  }

  return Eval(code, std::move(locals));
}

rt::Value *Executor::Impl::Eval(Code *code, std::vector<rt::Value *> &&locals) {
  rt::Value *result;

  for (const unique<Statement> &statement : code->statements()) {
    switch (statement->kind()) {
      case kStReturn: {
        Return *st_return = statement->As<kStReturn>();

        result = locals[st_return->value()];
        goto end;
      }

      case kDirectCall: {
        DirectCall *st_direct_call = statement->As<kDirectCall>();

        size_t var = st_direct_call->var();
        size_t function_id = st_direct_call->function_id();
        std::vector<size_t> args_index = st_direct_call->args();
        size_t args_size = args_index.size();

        std::vector<rt::Value *> args(args_size);
        for (size_t i = 0; i < args_size; i++) {
          args[i] = locals[args_index[i]];
        }

        locals[var] = Call(function_id, args);
        break;
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
