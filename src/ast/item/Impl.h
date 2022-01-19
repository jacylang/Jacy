#ifndef JACY_AST_ITEM_IMPL_H
#define JACY_AST_ITEM_IMPL_H

#include "ast/item/Item.h"
#include "ast/fragments/Generics.h"

namespace jc::ast {
    struct Impl : Item {
        Impl(
            GenericParam::OptList && generics,
            PR<TypePath::Ptr> && traitTypePath,
            Type::OptPtr && forType,
            Item::List && members,
            Span span
        ) : Item {span, ItemKind::Impl},
            generics {std::move(generics)},
            traitTypePath {std::move(traitTypePath)},
            forType {std::move(forType)},
            members {std::move(members)} {}

        GenericParam::OptList generics;
        PR<TypePath::Ptr> traitTypePath;
        Type::OptPtr forType;
        Item::List members;

        span::Ident getName() const override {
            return Ident::empty();
        }

        NodeId::Opt getNameNodeId() const override {
            return None;
        }

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_ITEM_IMPL_H
