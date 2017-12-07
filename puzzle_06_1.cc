// Copyright (C) 2017, Seznam.cz, a.s.

#include <algorithm>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

size_t checksum(const std::vector<int>& nums) {
    size_t seed = 0;
    for (auto n : nums) {
        boost::hash_combine(seed, n);
    }
    return seed;
}


int main() {
    std::vector<int> nums;
    {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss{line};
        while (!ss.eof()) {
            int x;
            ss >> x;
            nums.push_back(x);
        }
    }

    std::unordered_set<size_t> hashes;
    hashes.insert(checksum(nums));

    int steps = 0;
    for(;;) {
        auto it = std::max_element(std::begin(nums), std::end(nums));
        if (it == std::end(nums)) {
            std::cerr << "NO MAX!\n";
            exit(1);
        }
        int val = 0;
        std::swap(val, *it);
        for(++it; val > 0; ++it, --val) {
            if (it == std::end(nums)) {
                it = std::begin(nums);
            }
            (*it)++;
        }
        ++steps;
        if (!hashes.insert(checksum(nums)).second) {
            break;
        }
    }

    std::cout << "steps: " << steps << "\n";
}
