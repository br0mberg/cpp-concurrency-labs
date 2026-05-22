#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

class AsyncLogger {
public:
    AsyncLogger();
    ~AsyncLogger();

    AsyncLogger(const AsyncLogger&) = delete;
    AsyncLogger& operator=(const AsyncLogger&) = delete;

    void log(const std::string& msg);

private:
    void run();

    std::queue<std::string> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_;
    std::thread worker_;
};
