#include "async_logger.h"

#include <iostream>

AsyncLogger::AsyncLogger() : stop_(false) {
    worker_ = std::thread(&AsyncLogger::run, this);
}

AsyncLogger::~AsyncLogger() {
    {
        std::lock_guard<std::mutex> lk(mutex_);
        stop_ = true;
    }
    cv_.notify_one();
    if (worker_.joinable()) worker_.join();
}

void AsyncLogger::log(const std::string& msg) {
    {
        std::lock_guard<std::mutex> lk(mutex_);
        queue_.push(msg);
    }
    cv_.notify_one();
}

void AsyncLogger::run() {
    for (;;) {
        std::unique_lock<std::mutex> lk(mutex_);
        cv_.wait(lk, [this] { return stop_ || !queue_.empty(); });

        while (!queue_.empty()) {
            std::string msg = std::move(queue_.front());
            queue_.pop();
            lk.unlock();
            std::cout << msg << '\n';
            lk.lock();
        }

        if (stop_) return;
    }
}
