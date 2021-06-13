#ifndef JACY_CORE_INTERFACE_H
#define JACY_CORE_INTERFACE_H

#include <string>
#include <vector>
#include <iostream>
#include <variant>
#include <filesystem>

#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "ast/AstPrinter.h"
#include "suggest/SuggDumper.h"
#include "suggest/Suggester.h"
#include "ast/Linter.h"
#include "resolve/NameResolver.h"
#include "resolve/ModuleTreeBuilder.h"
#include "common/Config.h"
#include "ast/Party.h"
#include "fs/fs.h"
#include "session/Session.h"

namespace jc::core {
    using common::Config;

    const auto bench = std::chrono::high_resolution_clock::now;

    class Interface {
    public:
        Interface();
        virtual ~Interface() = default;

        void compile();

    private:
        void init();
        void workflow();
        Config & config;

        // Parsing //
    private:
        parser::Lexer lexer;
        parser::Parser parser;
        ast::DirTreePrinter dirTreePrinter;
        ast::AstPrinter astPrinter;
        ast::Linter linter;
        dt::Option<ast::party_ptr> party;

        void parse();
        void lintAst();
        ast::dir_module_ptr parseDir(const fs::entry_ptr & dir, const std::string & ignore = "");
        ast::file_module_ptr parseFile(const fs::entry_ptr & file);

        // Debug //
        void printDirTree();
        void printSource(const parser::parse_sess_ptr & parseSess);
        void printTokens(const fs::path & path, const parser::token_list & tokens);
        void printAst(ast::AstPrinterMode mode);

        // Name resolution //
    private:
        resolve::ModuleTreeBuilder moduleTreeBuilder;
        resolve::ModulePrinter modulePrinter;
        resolve::NameResolver nameResolver;

        void resolveNames();

    private:
        common::Logger log{"Interface"};

        sess::sess_ptr sess;

        // Suggestions //
    private:
        sugg::sugg_list suggestions;
        void collectSuggestions(sugg::sugg_list && additional);
        void checkSuggestions(const std::string & stageName);

        // Benchmarks //
    private:
        using milli_ratio = std::ratio<1, 1000>;
        using bench_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

        enum class BenchmarkKind {
            Lexing,
            Parsing,
        };
        bench_t finalBenchStart;
        std::map<std::string, double> benchmarks;
        dt::Option<bench_t> lastBench;
        bool eachStageBenchmarks;
        void beginFinalBench();
        void printFinalBench();
        void beginBench();
        void endBench(const std::string & name, BenchmarkKind kind);
        void printBenchmarks() noexcept;
    };
}

#endif // JACY_CORE_INTERFACE_H
