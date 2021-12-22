#ifndef JACY_HIR_NODES_ITEMS_H
#define JACY_HIR_NODES_ITEMS_H

#include "hir/nodes/Item.h"
#include "hir/nodes/Expr.h"
#include "span/Ident.h"
#include "hir/nodes/Type.h"
#include "ast/fragments/func_fragments.h"

namespace jc::hir {
    struct Variant : HirNode {
        // TODO: Requires unification for AST `Enum` field types

        enum class Kind {
            Struct, // Struct variant (`{field: Type, ...}`)
            Tuple, // Tuple variant (`(Types...)`)
            Unit, // Variant with optional discriminant (such as `Foo = 1` or just `Bar`)
        };

        HirId hirId;
        span::Ident ident;
        span::Span span;

        // TODO: Add discriminant for Unit kind
    };

    struct Enum : Item {
        Enum(std::vector<Variant> && variants) : Item {ItemKind::Enum}, variants {std::move(variants)} {
        }

        std::vector<Variant> variants;
    };

    /// Identifier of the `Body` declared below
    /// For now, just a wrapper over `HirId`
    struct BodyId {
        HirId hirId;
    };

    /// Function body
    /// Separated from `Func` as it is type checked apart
    struct Body {
        Body(bool exprBody, Expr::Ptr && value) : exprBody {exprBody}, value {std::move(value)} {
        }

        /// Denotes that `func`'s body was defined with `=`
        bool exprBody;

        /// Function body value, BlockExpr if `func` was declared with `{}` and any expr if with `=`
        Expr::Ptr value;
    };

    /// Function signature used for raw `func`
    /// and `func` signatures without implementations (in traits)
    struct FuncSig {
        using ReturnType = ast::FuncReturnType<Type::Ptr>;

        FuncSig(Type::List && inputs, ReturnType && returnType)
            : inputs {std::move(inputs)}, returnType {std::move(returnType)} {
        }

        Type::List inputs;
        ReturnType returnType;
    };

    struct Func : Item {
        Func(FuncSig && sig, Body && body) : Item {ItemKind::Func}, sig {std::move(sig)}, body {std::move(body)} {
        }

        FuncSig sig;
        Body body;
    };

    struct Impl : Item {};

    struct Mod : Item {
        Mod(ItemId::List && items) : Item {ItemKind::Mod}, items {std::move(items)} {
        }

        ItemId::List items;
    };

    struct Struct : Item {};

    struct Trait : Item {};

    struct TypeAlias : Item {};

    struct UseDecl : Item {};
}

#endif // JACY_HIR_NODES_ITEMS_H
