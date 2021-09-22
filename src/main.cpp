#include "core/Jacy.h"

int main(int argc, const char ** argv) {
    jc::core::Jacy jacy;
    try {
        return jacy.meow(argc, argv);
    } catch (const std::exception & e) {
        std::cout << "Uncaught error: " << e.what() << std::endl;

        if (jc::config::Config::getInstance().checkDevMode()) {
            throw;
        }

        return 1;
    }
}
