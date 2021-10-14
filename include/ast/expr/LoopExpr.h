#ifndef JACY_AST_EXPR_LOOPEXPR_H
#define JACY_AST_EXPR_LOOPEXPR_H

#include "ast/expr/Expr.h"

#include <utility>
#include "Block.h"

namespace jc::ast {
    struct LoopExpr : Expr {
        LoopExpr(Block::Ptr && body, Span span)
            : Expr{span, ExprKind::Loop}, body{std::move(body)} {}

        Block::Ptr body;

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_EXPR_LOOPEXPR_H
