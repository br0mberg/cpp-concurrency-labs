#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

struct Resource {
    std::mutex mutex;
};

std::atomic<int> success_count{0};
Resource resource_a;
Resource resource_b;

void polite_worker(Resource& first, Resource& second, int id) {
    std::mt19937 generator(static_cast<std::uint32_t>(
        std::chrono::steady_clock::now().time_since_epoch().count()) + id);
    std::uniform_int_distribution<int> delay_microseconds(50, 500);

    for (int completed = 0; completed < 10000;) {
        first.mutex.lock();
        if (second.mutex.try_lock()) {
            ++success_count;
            second.mutex.unlock();
            first.mutex.unlock();
            ++completed;
            continue;
        }

        first.mutex.unlock();
        std::this_thread::sleep_for(
            std::chrono::microseconds(delay_microseconds(generator)));
    }
}

int main() {
    const auto start = std::chrono::steady_clock::now();

    std::thread first(polite_worker, std::ref(resource_a), std::ref(resource_b), 1);
    std::thread second(polite_worker, std::ref(resource_b), std::ref(resource_a), 2);
    first.join();
    second.join();

    const auto elapsed = std::chrono::duration<double>(
        std::chrono::steady_clock::now() - start);
    std::cout << "Operations: " << success_count << "\n";
    std::cout << "Time: " << elapsed.count() << "s\n";
}
