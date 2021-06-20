#ifndef JACY_AST_LINTER_H
#define JACY_AST_LINTER_H

#include "common/Logger.h"
#include "ast/BaseVisitor.h"
#include "ast/nodes.h"
#include "suggest/BaseSugg.h"
#include "data_types/SuggResult.h"
#include "suggest/SuggInterface.h"

namespace jc::ast {
    using common::Logger;

    /// LinterContext - collection of contexts for linting that only needed for context-dependent constructions,
    /// for example, `break` can appear only inside loop-like context, but `if` does not bring any kind of this
    /// dependency.
    /// Note: These are not actual `Func`, `Loop` and `Struct` nodes.
    enum class LinterContext {
        Func,
        Loop,
        Struct,
    };

    class Linter : public BaseVisitor, public sugg::SuggInterface {
    public:
        Linter();

        dt::SuggResult<dt::none_t> lint(const Party & party);

    private:
        void visit(const ErrorNode & errorNode) override;
        void visit(const File & file) override;

        void visit(const RootModule & rootModule) override;
        void visit(const FileModule & fileModule) override;
        void visit(const DirModule & dirModule) override;

        // Items //
        void visit(const Enum & enumDecl) override;
        void visit(const EnumEntry & enumEntry) override;
        void visit(const Func & func) override;
        void visit(const FuncParam & funcParam) override;
        void visit(const Impl & impl) override;
        void visit(const Mod & mod) override;
        void visit(const Struct & _struct) override;
        void visit(const StructField & field) override;
        void visit(const Trait & trait) override;
        void visit(const TypeAlias & typeAlias) override;
        void visit(const UseDecl & useDecl) override;
        void visit(const UseTreeRaw & useTree) override;
        void visit(const UseTreeSpecific & useTree) override;
        void visit(const UseTreeRebind & useTree) override;
        void visit(const UseTreeAll & useTree) override;

        // Statements //
        void visit(const ExprStmt & exprStmt) override;
        void visit(const ForStmt & forStmt) override;
        void visit(const ItemStmt & itemStmt) override;
        void visit(const LetStmt & letStmt) override;
        void visit(const WhileStmt & whileStmt) override;

        // Expressions //
        void visit(const Assignment & assign) override;
        void visit(const Block & block) override;
        void visit(const BorrowExpr & borrowExpr) override;
        void visit(const BreakExpr & breakExpr) override;
        void visit(const ContinueExpr & continueExpr) override;
        void visit(const DerefExpr & derefExpr) override;
        void visit(const IfExpr & ifExpr) override;
        void visit(const Infix & infix) override;
        void visit(const Invoke & invoke) override;
        void visit(const Lambda & lambdaExpr) override;
        void visit(const LambdaParam & param) override;
        void visit(const ListExpr & listExpr) override;
        void visit(const LiteralConstant & literalConstant) override;
        void visit(const LoopExpr & loopExpr) override;
        void visit(const MemberAccess & memberAccess) override;
        void visit(const ParenExpr & parenExpr) override;
        void visit(const PathExpr & pathExpr) override;
        void visit(const PathExprSeg & seg) override;
        void visit(const Prefix & prefix) override;
        void visit(const QuestExpr & questExpr) override;
        void visit(const ReturnExpr & returnExpr) override;
        void visit(const SpreadExpr & spreadExpr) override;
        void visit(const StructExpr & structExpr) override;
        void visit(const StructExprField & field) override;
        void visit(const Subscript & subscript) override;
        void visit(const ThisExpr & thisExpr) override;
        void visit(const TupleExpr & tupleExpr) override;
        void visit(const UnitExpr & unitExpr) override;
        void visit(const WhenExpr & whenExpr) override;
        void visit(const WhenEntry & entry) override;

        // Types //
        void visit(const ParenType & parenType) override;
        void visit(const TupleType & tupleType) override;
        void visit(const TupleTypeEl & el) override;
        void visit(const FuncType & funcType) override;
        void visit(const SliceType & listType) override;
        void visit(const ArrayType & arrayType) override;
        void visit(const TypePath & typePath) override;
        void visit(const TypePathSeg & seg) override;
        void visit(const UnitType & unitType) override;

        // Type params //
        void visit(const GenericType & genericType) override;
        void visit(const Lifetime & lifetime) override;
        void visit(const ConstParam & constParam) override;

        // Fragments //
        void visit(const Attribute & attr) override;
        void visit(const Identifier & id) override;
        void visit(const NamedElement & el) override;
        void visit(const SimplePath & path) override;
        void visit(const SimplePathSeg & seg) override;

        // Patterns //
        void visit(const LiteralPattern & pat) override;
        void visit(const IdentPattern & pat) override;
        void visit(const SpreadPattern & pat) override;


        // Helpers //
    private:
        bool isPlaceExpr(const expr_ptr & expr);

        template<class T>
        void lintEach(const std::vector<T> & entities) {
            for (const auto & entity : entities) {
                entity->accept(*this);
            }
        }

        template<class T>
        void lintEach(const std::vector<PR<T>> & entities) {
            for (const auto & entity : entities) {
                entity.accept(*this);
            }
        }

        // Context //
    private:
        std::vector<LinterContext> ctxStack;
        bool isInside(LinterContext ctx);
        bool isDeepInside(LinterContext ctx);
        void pushContext(LinterContext ctx);
        void popContext();

        common::Logger log{"linter"};
    };
}

#endif //JACY_AST_LINTER_H
