#include "execution/lethargy/executor.h"

#include "common/memory.h"

#include "metamodel/cfg/cfg.h"
#include "metamodel/cfg/statements.h"
#include "metamodel/types.h"

namespace ai {
Executor::Executor(CFG *cfg, MemoryView *mview) : cfg_(cfg), mview_(mview) {}

cref<Artefact> Executor::Start() {
  cref<Artefact> result;
  ArrayOfPointer aop(*mview_);

  CFG::Block *block = cfg_->entry();
  for (const std::unique_ptr<Statement> &statement : block->statements) {
    switch (statement->kind()) {
      case Statement::kReturn: {
        result = aop.Get<Artefact>(statement->Op<Return::Value>());
      }

      case Statement::kStringLiteral: {
        size_t &left = statement->Op<StringLiteral::Left>();
        const std::string &right = statement->Op<StringLiteral::Right>();

        // aop.Set(left, &right);
      }
    }
  }

  return result;
}
}  // namespace ai
