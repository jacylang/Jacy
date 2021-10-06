#ifndef JACY_RESOLVE_NAMERESOLVER_H
#define JACY_RESOLVE_NAMERESOLVER_H

#include "ast/StubVisitor.h"
#include "resolve/Rib.h"
#include "utils/arr.h"
#include "message/MessageBuilder.h"
#include "resolve/Resolutions.h"
#include "resolve/PathResolver.h"

namespace jc::resolve {
    using log::Logger;

    class NameResolver : public ast::StubVisitor {
    public:
        NameResolver();
        ~NameResolver() override = default;

        message::MessageHolder::Result<dt::none_t> resolve(const sess::Session::Ptr & sess, const ast::Party & party);

        // Items //
//        void visit(const ast::Enum & enumDecl) override;
        void visit(const ast::Func & func) override;
        void visit(const ast::Impl & impl) override;
        void visit(const ast::Mod & mod) override;
        void visit(const ast::Struct & _struct) override;
        void visit(const ast::Trait & trait) override;
        //        void visit(const ast::TypeAlias & typeAlias) override;
        void visit(const ast::Init & init) override;

        // Statements //
        void visit(const ast::LetStmt & letStmt) override;

        // Expressions //
        void visit(const ast::Block & block) override;
        void visit(const ast::Lambda & lambda) override;
        void visit(const ast::PathExpr & pathExpr) override;
        void visit(const ast::MatchArm & arm) override;
        void visit(const ast::Invoke & invoke) override;

        // Types //
        void visit(const ast::TypePath & typePath) override;

        // Patterns //
        void visit(const ast::IdentPat & pat) override;
        void visit(const ast::PathPat & pat) override;
        void visit(const ast::StructPat & pat) override;

    private:
        using ast::StubVisitor::visit;

    private:
        log::Logger log{"NameResolver"};
        sess::Session::Ptr sess;
        config::Config & config;

        // Ribs //
    private:
        // TODO: Think about struct-of-arrays (PerNS<vector<Rib>>)
        Rib::Stack ribStack;
        size_t getDepth() const;
        const Rib::Ptr & curRib() const;
        void enterRootRib();
        void enterRib(Rib::Kind kind = Rib::Kind::Raw);
        void enterModule(Symbol name, Namespace ns = Namespace::Type, Rib::Kind kind = Rib::Kind::Raw);
        void enterFuncModule(Symbol baseName, Symbol suffix);
        void enterBlock(NodeId nodeId, Rib::Kind kind = Rib::Kind::Raw);
        void exitRib();
        void liftToDepth(size_t prevDepth);

        // Modules //
    private:
        /// Last met module
        /// We need to store it because some ribs do not bind modules
        Module::Ptr currentModule;

        // Definitions //
    private:
        void defineLocal(NodeId localNodeId, const ast::Ident::PR & ident);

        // Resolution //
    private:
        PathResolver pathResolver;
        Resolutions _resolutions;
        void resolveSimplePath(const ast::SimplePath & simplePath);
        void resolvePath(Namespace targetNS, const ast::Path & path, const Symbol::Opt & suffix = None);
        bool resolveLocal(const Symbol & name, const ast::Path & path);

        // Messages //
    private:
        message::MessageHolder msg;

        void suggestAltNames(Namespace target, const Symbol & name, const PerNS<NameBinding::Opt> & altDefs);

        // Debug //
    private:
        bool printRibsFlag{false};
        std::string ribsDebugOutput;

        void printRib();
        void dumpRibs();

        std::vector<std::string> scopePath;
        void appendModulePath(const Symbol & modName, DefId defId);
        void appendBlockPath(NodeId nodeId);
        void appendCustomPath(const std::string & segment);
        void removePathSeg();
    };
}

#endif // JACY_RESOLVE_NAMERESOLVER_H
