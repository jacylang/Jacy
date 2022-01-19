#ifndef JACY_AST_EXPR_SPREADEXPR_H
#define JACY_AST_EXPR_SPREADEXPR_H

#include "ast/expr/Expr.h"

namespace jc::ast {
    // Make a fragment and remove from Expr
    struct SpreadExpr : Expr {
        SpreadExpr(const parser::Token & token, Expr::Ptr && expr, Span span)
            : Expr {span, ExprKind::Spread}, token {token}, expr {std::move(expr)} {}

        parser::Token token;
        Expr::Ptr expr;

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_EXPR_SPREADEXPR_H
