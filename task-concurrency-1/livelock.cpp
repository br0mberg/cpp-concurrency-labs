#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

struct Resource {
    std::mutex m;
};

std::atomic<int> success_count{0};
Resource res_a;
Resource res_b;

void polite_worker(Resource& r1, Resource& r2, int id) {
    for (int i = 0; i < 10000; ++i) {
        r1.m.lock();

        if (r2.m.try_lock()) {
            success_count++;
            r2.m.unlock();
            r1.m.unlock();
        } else {
            r1.m.unlock();

            // std::this_thread::yield(); не поможет!
            i--;
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::thread t1(polite_worker, std::ref(res_a), std::ref(res_b), 1);
    std::thread t2(polite_worker, std::ref(res_b), std::ref(res_a), 2);

    t1.join();
    t2.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Operations: " << success_count << "\n";
    std::cout << "Time: " << std::chrono::duration<double>(end - start).count() << "s\n";
}
