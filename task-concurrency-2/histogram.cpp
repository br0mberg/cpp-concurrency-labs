#include "common.h"

#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {
    const size_t N = get_data_size(argc, argv);
    auto data = generate_data(N);

    auto start = std::chrono::high_resolution_clock::now();
    auto counts = histogram_sequential(data);
    auto end = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(end - start).count();

    long long total = 0;
    for (int c : counts) total += c;

    std::cout << "Method: sequential" << std::endl;
    std::cout << "Threads: 1" << std::endl;
    std::cout << "Time: " << ms << " ms" << std::endl;
    std::cout << "Correct: " << (total == static_cast<long long>(N) ? "true" : "false") << std::endl;

    return 0;
}
