#ifndef JACY_AST_VALIDATOR_H
#define JACY_AST_VALIDATOR_H

#include "log/Logger.h"
#include "ast/BaseVisitor.h"
#include "ast/Party.h"
#include "message/Message.h"
#include "message/MessageBuilder.h"
#include "message/MessageResult.h"

namespace jc::ast {
    using log::Logger;

    /// ValidatorCtx - collection of contexts for validation that only needed for context-dependent constructions,
    /// for example, `break` can appear only inside loop-like context, but `if` does not bring any kind of this
    /// dependency.
    /// Note: These are not actual `Func`, `Loop` and `Struct` nodes.
    enum class ValidatorCtx {
        Func,
        Loop,
        Struct,
    };

    class Validator : public BaseVisitor {
    public:
        Validator();

        message::MessageResult<dt::none_t> lint(const Party & party);

    private:
        void visit(const ErrorNode & errorNode) override;

        // Items //
        void visit(const Const & constItem) override;

        void visit(const Enum & enumDecl) override;

        void visit(const Variant & variant) override;

        void visit(const Func & func) override;

        void visit(const FuncParam & funcParam) override;

        void visit(const Impl & impl) override;

        void visit(const Mod & mod) override;

        void visit(const Struct & st) override;

        void visit(const Trait & trait) override;

        void visit(const TypeAlias & typeAlias) override;

        void visit(const UseDecl & useDecl) override;

        void visit(const UseTree & useTree) override;

        void visit(const Init & init) override;

        // Statements //
        void visit(const ExprStmt & exprStmt) override;

        void visit(const ItemStmt & itemStmt) override;

        void visit(const LetStmt & letStmt) override;

        // Expressions //
        void visit(const Assign & assign) override;

        void visit(const Block & block) override;

        void visit(const BorrowExpr & borrowExpr) override;

        void visit(const BreakExpr & breakExpr) override;

        void visit(const ContinueExpr & continueExpr) override;

        void visit(const ForExpr & forStmt) override;

        void visit(const IfExpr & ifExpr) override;

        void visit(const Infix & infix) override;

        void visit(const Invoke & invoke) override;

        void visit(const Lambda & lambdaExpr) override;

        void visit(const LambdaParam & param) override;

        void visit(const ListExpr & listExpr) override;

        void visit(const LitExpr & literalConstant) override;

        void visit(const LoopExpr & loopExpr) override;

        void visit(const FieldExpr & memberAccess) override;

        void visit(const ParenExpr & parenExpr) override;

        void visit(const PathExpr & pathExpr) override;

        void visit(const Prefix & prefix) override;

        void visit(const Postfix & questExpr) override;

        void visit(const ReturnExpr & returnExpr) override;

        void visit(const SpreadExpr & spreadExpr) override;

        void visit(const Subscript & subscript) override;

        void visit(const SelfExpr & selfExpr) override;

        void visit(const TupleExpr & tupleExpr) override;

        void visit(const UnitExpr & unitExpr) override;

        void visit(const MatchExpr & matchExpr) override;

        void visit(const MatchArm & matchArm) override;

        void visit(const WhileExpr & whileStmt) override;

        // Types //
        void visit(const ParenType & parenType) override;

        void visit(const TupleType & tupleType) override;

        void visit(const FuncType & funcType) override;

        void visit(const SliceType & listType) override;

        void visit(const ArrayType & arrayType) override;

        void visit(const TypePath & typePath) override;

        void visit(const UnitType & unitType) override;

        // Type params //
        virtual void visit(const GenericParam & param) override;

        virtual void visit(const GenericArg & arg) override;

        // Fragments //
        void visit(const Attr & attr) override;

        void visit(const Ident & id) override;

        void visit(const Path & path) override;

        void visit(const PathSeg & seg) override;

        void visit(const SimplePath & path) override;

        void visit(const SimplePathSeg & seg) override;

        void visit(const AnonConst & anonConst) override;

        // Patterns //
        void visit(const MultiPat & pat) override;

        void visit(const ParenPat & pat) override;

        void visit(const LitPat & pat) override;

        void visit(const IdentPat & pat) override;

        void visit(const RefPat & pat) override;

        void visit(const PathPat & pat) override;

        void visit(const WildcardPat & pat) override;

        void visit(const RestPat & pat) override;

        void visit(const StructPat & pat) override;

        void visit(const TuplePat & pat) override;

        void visit(const SlicePat & pat) override;

    private:
        void validateFuncSig(const FuncSig & sig);

    private:
        message::MessageHolder msg;

        // Helpers //
    private:
        bool isPlaceExpr(const Expr::Ptr & expr);

        template<class T>
        void validateEach(const std::vector<T> & entities) {
            for (const auto & entity : entities) {
                if constexpr (dt::is_ptr_like<T>::value) {
                    entity->accept(*this);
                } else {
                    entity.accept(*this);
                }
            }
        }

        template<class T>
        void validateEach(const std::vector<PR<T>> & entities) {
            for (const auto & entity : entities) {
                entity.autoAccept(*this);
            }
        }

        void validateAttrs(const ast::Attr::List & attrs);

        template<class N>
        void validateNamedNodeList(const typename NamedNode<N, Ident::OptPR>::List & els) {
            for (const auto & el : els) {
                el.name.then([&](const Ident::PR & name) {
                    name.autoAccept(*this);
                });
                el.node.autoAccept(*this);
            }
        }

        // Context //
    private:
        std::vector<ValidatorCtx> ctxStack;

        bool isInside(ValidatorCtx ctx);

        bool isDeepInside(ValidatorCtx ctx);

        void pushContext(ValidatorCtx ctx);

        void popContext();

        log::Logger log {"ast-validator"};
    };
}

#endif // JACY_AST_VALIDATOR_H
