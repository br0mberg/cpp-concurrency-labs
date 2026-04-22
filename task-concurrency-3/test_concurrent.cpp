#include "async_logger.h"

#include <iostream>
#include <string>
#include <thread>
#include <vector>

int main() {
    {
        AsyncLogger logger;
        std::vector<std::thread> threads;
        for (int t = 0; t < 4; ++t) {
            threads.emplace_back([&logger, t]() {
                for (int i = 0; i < 25; ++i) {
                    logger.log("t" + std::to_string(t) + "-" + std::to_string(i));
                }
            });
        }
        for (auto& th : threads) {
            th.join();
        }
    }
    std::cerr << "Test concurrent: completed" << std::endl;
    return 0;
}
