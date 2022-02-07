#ifndef JACY_AST_EXPR_CONTINUEEXPR_H
#define JACY_AST_EXPR_CONTINUEEXPR_H

#include "ast/expr/Expr.h"

namespace jc::ast {
    /// `continue`
    struct ContinueExpr : Expr {
        explicit ContinueExpr(Span span) : Expr {span, Expr::Kind::Continue} {}

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_EXPR_CONTINUEEXPR_H
