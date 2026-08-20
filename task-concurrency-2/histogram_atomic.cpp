#include "common.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

static unsigned pick_threads() {
    const unsigned available = std::thread::hardware_concurrency();
    return std::clamp(available == 0 ? 4u : available, 4u, 8u);
}

int main(int argc, char* argv[]) {
    const size_t size = get_data_size(argc, argv);
    const auto data = generate_data(size);
    const unsigned thread_count = pick_threads();
    std::vector<std::atomic<int>> atomic_counts(256);

    const auto start = std::chrono::steady_clock::now();
    std::vector<std::thread> threads;
    threads.reserve(thread_count);
    for (unsigned thread = 0; thread < thread_count; ++thread) {
        const size_t begin = size * thread / thread_count;
        const size_t end = size * (thread + 1) / thread_count;
        threads.emplace_back([&, begin, end] {
            for (size_t index = begin; index < end; ++index) {
                atomic_counts[data[index]].fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    for (auto& thread : threads) {
        thread.join();
    }

    std::vector<int> counts(256);
    for (size_t index = 0; index < counts.size(); ++index) {
        counts[index] = atomic_counts[index].load(std::memory_order_relaxed);
    }
    const auto elapsed = std::chrono::duration<double, std::milli>(
        std::chrono::steady_clock::now() - start);
    std::cout << "Method: atomic\n";
    std::cout << "Threads: " << thread_count << "\n";
    std::cout << "Time: " << elapsed.count() << " ms\n";
    std::cout << "Correct: "
              << (verify(counts, histogram_sequential(data)) ? "true" : "false")
              << "\n";
}
