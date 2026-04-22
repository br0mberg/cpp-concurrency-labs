#pragma once

#include <vector>
#include <cstdint>
#include <cstdlib>
#include <random>

const size_t DEFAULT_DATA_SIZE = 100'000'000;

inline size_t get_data_size(int argc, char* argv[]) {
    if (argc > 1) return std::stoull(argv[1]);
    return DEFAULT_DATA_SIZE;
}

inline std::vector<uint8_t> generate_data(size_t n, unsigned seed = 42) {
    std::mt19937 gen(seed);
    std::vector<uint8_t> data(n);
    for (auto& b : data) b = static_cast<uint8_t>(gen() % 256);
    return data;
}

inline std::vector<int> histogram_sequential(const std::vector<uint8_t>& data) {
    std::vector<int> counts(256, 0);
    for (auto b : data) ++counts[b];
    return counts;
}

inline bool verify(const std::vector<int>& result, const std::vector<int>& reference) {
    if (result.size() != 256 || reference.size() != 256) return false;
    for (int i = 0; i < 256; ++i) {
        if (result[i] != reference[i]) return false;
    }
    return true;
}
