#ifndef JACY_BASEVISITOR_H
#define JACY_BASEVISITOR_H

namespace jc::ast {
    struct ErrorNode;

    struct File;
    struct Dir;

    // Items //
    struct Enum;
    struct EnumEntry;
    struct Func;
    struct FuncParam;
    struct Impl;
    struct Mod;
    struct Struct;
    struct StructField;
    struct Trait;
    struct TypeAlias;
    struct UseDecl;
    struct UseTreeRaw;
    struct UseTreeSpecific;
    struct UseTreeRebind;
    struct UseTreeAll;

    // Statements //
    struct ExprStmt;
    struct ForStmt;
    struct ItemStmt;
    struct LetStmt;
    struct WhileStmt;

    // Expressions //
    struct Assignment;
    struct Block;
    struct BorrowExpr;
    struct BreakExpr;
    struct ContinueExpr;
    struct DerefExpr;
    struct IfExpr;
    struct Infix;
    struct Invoke;
    struct Lambda;
    struct LambdaParam;
    struct ListExpr;
    struct LiteralConstant;
    struct LoopExpr;
    struct MemberAccess;
    struct ParenExpr;
    struct PathExpr;
    struct PathExprSeg;
    struct Prefix;
    struct QuestExpr;
    struct ReturnExpr;
    struct SpreadExpr;
    struct StructExpr;
    struct StructExprField;
    struct Subscript;
    struct SelfExpr;
    struct TupleExpr;
    struct UnitExpr;
    struct MatchExpr;
    struct MatchArm;

    // Types //
    struct ParenType;
    struct TupleType;
    struct TupleTypeEl;
    struct FuncType;
    struct SliceType;
    struct ArrayType;
    struct TypePath;
    struct TypePathSeg;
    struct UnitType;

    // Type params //
    struct TypeParam;
    struct Lifetime;
    struct ConstParam;

    // Fragments //
    struct Attribute;
    struct Identifier;
    struct Arg;
    struct SimplePath;
    struct SimplePathSeg;

    // Patterns //
    struct ParenPat;
    struct LitPat;
    struct BorrowPat;
    struct RefPattern;
    struct WCPat;
    struct SpreadPat;

    class BaseVisitor {
    public:
        virtual ~BaseVisitor() = default;

        virtual void visit(const ErrorNode&) = 0;
        virtual void visit(const File&) = 0;
        virtual void visit(const Dir&) = 0;

        // Items //
        virtual void visit(const Enum&) = 0;
        virtual void visit(const EnumEntry&) = 0;
        virtual void visit(const Func&) = 0;
        virtual void visit(const FuncParam&) = 0;
        virtual void visit(const Impl&) = 0;
        virtual void visit(const Mod&) = 0;
        virtual void visit(const Struct&) = 0;
        virtual void visit(const StructField&) = 0;
        virtual void visit(const Trait&) = 0;
        virtual void visit(const TypeAlias&) = 0;
        virtual void visit(const UseDecl&) = 0;
        virtual void visit(const UseTreeRaw&) = 0;
        virtual void visit(const UseTreeSpecific&) = 0;
        virtual void visit(const UseTreeRebind&) = 0;
        virtual void visit(const UseTreeAll&) = 0;

        // Statements //
        virtual void visit(const ExprStmt&) = 0;
        virtual void visit(const ForStmt&) = 0;
        virtual void visit(const ItemStmt&) = 0;
        virtual void visit(const LetStmt&) = 0;
        virtual void visit(const WhileStmt&) = 0;

        // Expressions //
        virtual void visit(const Assignment&) = 0;
        virtual void visit(const Block&) = 0;
        virtual void visit(const BorrowExpr&) = 0;
        virtual void visit(const BreakExpr&) = 0;
        virtual void visit(const ContinueExpr&) = 0;
        virtual void visit(const DerefExpr&) = 0;
        virtual void visit(const IfExpr&) = 0;
        virtual void visit(const Infix&) = 0;
        virtual void visit(const Invoke&) = 0;
        virtual void visit(const Lambda&) = 0;
        virtual void visit(const LambdaParam&) = 0;
        virtual void visit(const ListExpr&) = 0;
        virtual void visit(const LiteralConstant&) = 0;
        virtual void visit(const LoopExpr&) = 0;
        virtual void visit(const MemberAccess&) = 0;
        virtual void visit(const ParenExpr&) = 0;
        virtual void visit(const PathExpr&) = 0;
        virtual void visit(const PathExprSeg&) = 0;
        virtual void visit(const Prefix&) = 0;
        virtual void visit(const QuestExpr&) = 0;
        virtual void visit(const ReturnExpr&) = 0;
        virtual void visit(const SpreadExpr&) = 0;
        virtual void visit(const StructExpr&) = 0;
        virtual void visit(const StructExprField&) = 0;
        virtual void visit(const Subscript&) = 0;
        virtual void visit(const SelfExpr&) = 0;
        virtual void visit(const TupleExpr&) = 0;
        virtual void visit(const UnitExpr&) = 0;
        virtual void visit(const MatchExpr&) = 0;
        virtual void visit(const MatchArm&) = 0;

        // Types //
        virtual void visit(const ParenType&) = 0;
        virtual void visit(const TupleType&) = 0;
        virtual void visit(const TupleTypeEl&) = 0;
        virtual void visit(const FuncType&) = 0;
        virtual void visit(const SliceType&) = 0;
        virtual void visit(const ArrayType&) = 0;
        virtual void visit(const TypePath&) = 0;
        virtual void visit(const TypePathSeg&) = 0;
        virtual void visit(const UnitType&) = 0;

        // Type params //
        virtual void visit(const TypeParam&) = 0;
        virtual void visit(const Lifetime&) = 0;
        virtual void visit(const ConstParam&) = 0;

        // Fragments //
        virtual void visit(const Attribute&) = 0;
        virtual void visit(const Identifier&) = 0;
        virtual void visit(const Arg&) = 0;
        virtual void visit(const SimplePath&) = 0;
        virtual void visit(const SimplePathSeg&) = 0;

        // Patterns //
        virtual void visit(const ParenPat&) = 0;
        virtual void visit(const LitPat&) = 0;
        virtual void visit(const BorrowPat&) = 0;
        virtual void visit(const RefPattern&) = 0;
        virtual void visit(const WCPat&) = 0;
        virtual void visit(const SpreadPat&) = 0;
    };
}

#endif // JACY_BASEVISITOR_H
