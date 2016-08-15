#include "execution/lethargy/executor.h"

#include "execution/lethargy/memory.h"

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
      case Statement::kStringLiteral: {
        Identifier *left = statement->op<StringLiteral::Left>();
        std::string *right = statement->op<StringLiteral::Right>();

        mview_->Set(left->pos(), right);
      }
    }

    return result;
  }
}  // namespace ai
