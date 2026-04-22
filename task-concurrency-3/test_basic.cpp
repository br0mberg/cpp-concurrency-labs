#include "async_logger.h"

#include <iostream>
#include <string>

int main() {
    {
        AsyncLogger logger;
        for (int i = 0; i < 10; ++i) {
            logger.log("basic-" + std::to_string(i));
        }
    }
    std::cerr << "Test basic: completed" << std::endl;
    return 0;
}
