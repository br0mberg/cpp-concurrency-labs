#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

struct Resource {
    std::mutex mutex;
};

std::atomic<int> success_count{0};
Resource resource_a;
Resource resource_b;

void polite_worker(Resource& first, Resource& second) {
    for (int i = 0; i < 10000; ++i) {
        std::scoped_lock lock(first.mutex, second.mutex);
        ++success_count;
    }
}

int main() {
    const auto start = std::chrono::steady_clock::now();

    std::thread first(polite_worker, std::ref(resource_a), std::ref(resource_b));
    std::thread second(polite_worker, std::ref(resource_b), std::ref(resource_a));
    first.join();
    second.join();

    const auto elapsed = std::chrono::duration<double>(
        std::chrono::steady_clock::now() - start);
    std::cout << "Operations: " << success_count << "\n";
    std::cout << "Time: " << elapsed.count() << "s\n";
}
