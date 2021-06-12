#include "ast/DirTreePrinter.h"
#include "ast/Party.h"

namespace jc::ast {
    void DirTreePrinter::visit(const RootModule & rootModule) {
        common::Logger::print(".");
        common::Logger::nl();
        common::Logger::print("|-- ");
        rootModule.getRootFile()->accept(*this);
        rootModule.getRootDir()->accept(*this);
    }

    void DirTreePrinter::visit(const DirModule & dirModule) {
        printIndent();
        common::Logger::print("|--", dirModule.getName() + "/");
        common::Logger::nl();
        indent++;
        for (size_t i = 0; i < dirModule.getModules().size(); i++) {
            printIndent();
            if (i < dirModule.getModules().size() - 1) {
                common::Logger::print("|-- ");
            }

            const auto & module = dirModule.getModules().at(i);
            module->accept(*this);
        }
        indent--;
        printIndent();
    }

    void DirTreePrinter::visit(const FileModule & fileModule) {
        common::Logger::print(fileModule.getName());
        common::Logger::nl();
    }

    void DirTreePrinter::printIndent() {
        common::Logger::print(utils::str::repeat(" ", indent));
    }
}