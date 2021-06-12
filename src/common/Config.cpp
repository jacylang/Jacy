#include "common/Config.h"

#include <iostream>

namespace jc::common {
    Config::Config() = default;

    void Config::applyCliConfig(const cli::Args & cliConfig) {
        rootFile = cliConfig.getRootFile();

        // Apply key-value args //

        // `print`
        const auto & printVals = cliConfig.getValues("print");
        if (printVals) {
            for (const auto & val : printVals.unwrap()) {
                if (val == "dir-tree") {
                    print.insert(PrintKind::DirTree);
                } else if (val == "ast") {
                    print.insert(PrintKind::Ast);
                } else if (val == "tokens") {
                    print.insert(PrintKind::Tokens);
                } else if (val == "sugg") {
                    print.insert(PrintKind::Suggestions);
                } else if (val == "source") {
                    print.insert(PrintKind::Source);
                } else if (val == "names") {
                    print.insert(PrintKind::Names);
                } else if (val == "all") {
                    print.insert(PrintKind::All);
                } else {
                    throw std::logic_error("[Config] Unhandled value for `print` cli argument");
                }
            }
        }

        // `compile-depth`
        const auto & maybeCompileDepth = cliConfig.getSingleValue("compile-depth");
        if (maybeCompileDepth) {
            const auto & cd = maybeCompileDepth.unwrap();
            if (cd == "parser") {
                compileDepth = CompileDepth::Parser;
            } else if (cd == "name-resolution") {
                compileDepth = CompileDepth::NameResolution;
            } else {
                throw std::logic_error("[Config] Unhandled value for `compile-depth` cli argument");
            }
        }

        // `benchmark`
        const auto & maybeBenchmark = cliConfig.getSingleValue("benchmark");
        if (maybeBenchmark) {
            const auto & bmk = maybeBenchmark.unwrap();
            if (bmk == "final") {
                benchmark = Benchmark::Final;
            } else if (bmk == "each-stage") {
                benchmark = Benchmark::EachStage;
            } else {
                throw std::logic_error("[Config] Unhandled value for `benchmark` cli argument");
            }
        }

        const auto & maybeLogLevel = cliConfig.getSingleValue("log-level");
        if (maybeLogLevel) {
            const auto & ll = maybeLogLevel.unwrap();
            if (ll == "dev") {
                logLevel = LogLevel::Dev;
            } else if (ll == "debug") {
                logLevel = LogLevel::Debug;
            } else if (ll == "info") {
                logLevel = LogLevel::Info;
            } else if (ll == "warn") {
                logLevel = LogLevel::Warn;
            } else if (ll == "error") {
                logLevel = LogLevel::Error;
            } else {
                throw std::logic_error("[Config] Unhandled value for `log-level` cli argument");
            }
        }

        // Apply bool args //
        dev = cliConfig.is("dev");
    }

    // Checkers //
    bool Config::checkMode(Mode mode) const {
        return this->mode == mode;
    }

    bool Config::checkPrint(PrintKind printKind) const {
        return print.find(PrintKind::All) != print.end() or print.find(printKind) != print.end();
    }

    bool Config::checkBenchmark(Benchmark benchmark) const {
        return this->benchmark == benchmark;
    }

    bool Config::checkDev() const {
        return dev;
    }

    bool Config::checkCompileDepth(CompileDepth compileDepth) const {
        return static_cast<uint8_t>(this->compileDepth) <= static_cast<uint8_t>(compileDepth);
    }

    bool Config::checkLogLevel(LogLevel logLevel) const {
        return static_cast<uint8_t>(this->logLevel) <= static_cast<uint8_t>(logLevel);
    }

    Config::LogLevel Config::getLogLevel() const {
        return logLevel;
    }

    const std::string & Config::getRootFile() const {
        return rootFile;
    }
}
