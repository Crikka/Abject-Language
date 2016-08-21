#include "execution/lethargy/executor.h"

#include "common/memory.h"

#include "metamodel/cfg/cfg.h"
#include "metamodel/cfg/statements.h"
#include "metamodel/types.h"

namespace ai {
Executor::Executor(CFG *cfg, MemoryView *mview) : cfg_(cfg), mview_(mview) {}

cref<Model> Executor::Start() {
  cref<Model> result;

  CFG::Block *block = cfg_->entry();
  for (const std::unique_ptr<Statement> &statement : block->statements) {
    switch (statement->kind()) {
      case Statement::kReturn: {

      }

      case Statement::kStringLiteral: {
        Identifier &left = statement->Op<StringLiteral::Left>();
        const std::string &right = statement->Op<StringLiteral::Right>();

        // mview_->AsArrayOfPointer().Set(left.pos(), &right);
      }
    }
  }

  return result;
}
}  // namespace ai
