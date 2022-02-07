#ifndef JACY_AST_ITEM_INIT_H
#define JACY_AST_ITEM_INIT_H

#include "ast/item/Item.h"
#include "ast/fragments/func_fragments.h"

namespace jc::ast {
    struct Init : Item {
        Init(
            FuncSig && sig,
            Option<Body> && body,
            Span span
        ) : Item {span, Item::Kind::Init},
            sig {std::move(sig)},
            body {std::move(body)} {}

        FuncSig sig;
        Option<Body> body;

        span::Ident getName() const override {
            return span::Ident {span::Symbol::intern("init"), span.fromStartWithLen(4)};
        }

        NodeId::Opt getNameNodeId() const override {
            return None;
        }

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_ITEM_INIT_H
