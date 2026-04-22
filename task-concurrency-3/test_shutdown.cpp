#include "async_logger.h"

#include <iostream>
#include <string>

int main() {
    {
        AsyncLogger logger;
        for (int i = 0; i < 1000; ++i) {
            logger.log("shutdown-" + std::to_string(i));
        }
    }
    std::cerr << "Test shutdown: completed" << std::endl;
    return 0;
}
