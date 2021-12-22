#ifndef JACY_AST_EXPR_IFEXPR_H
#define JACY_AST_EXPR_IFEXPR_H

#include "ast/expr/Expr.h"

#include <utility>
#include "Block.h"

namespace jc::ast {
    /// If expression
    struct IfExpr : Expr {
        IfExpr(
            Expr::Ptr condition,
            Block::OptPtr ifBranch,
            Block::OptPtr elseBranch,
            Span span
        ) : Expr{span, ExprKind::If},
            condition{std::move(condition)},
            ifBranch{std::move(ifBranch)},
            elseBranch{std::move(elseBranch)} {}

        Expr::Ptr condition;
        Block::OptPtr ifBranch;
        Block::OptPtr elseBranch;

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_EXPR_IFEXPR_H
