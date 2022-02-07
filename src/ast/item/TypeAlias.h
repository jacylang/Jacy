#ifndef JACY_AST_ITEM_TYPEALIAS_H
#define JACY_AST_ITEM_TYPEALIAS_H

#include "ast/item/Item.h"
#include "ast/fragments/Ident.h"
#include "ast/fragments/Type.h"

namespace jc::ast {
    struct TypeAlias : Item {
        TypeAlias(
            Ident::PR && name,
            Type::OptPtr && type,
            Span span
        ) : Item {span, Item::Kind::TypeAlias},
            name {std::move(name)},
            type {std::move(type)} {}

        Ident::PR name;
        Type::OptPtr type;

        span::Ident getName() const override {
            return name.unwrap();
        }

        NodeId::Opt getNameNodeId() const override {
            return name.unwrap().id;
        }

        void accept(BaseVisitor & visitor) const override {
            return visitor.visit(*this);
        }
    };
}

#endif // JACY_AST_ITEM_TYPEALIAS_H
