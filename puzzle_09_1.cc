// Copyright (C) 2017, Seznam.cz, a.s.

#include <algorithm>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

size_t checksum(const std::vector<int>& nums)
{
    size_t seed = 0;
    for (auto n : nums) {
        boost::hash_combine(seed, n);
    }
    return seed;
}


int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        int level = 0;
        int sum = 0;

        bool skip = false;
        bool garbage = false;

        for (auto it = std::cbegin(line); it != std::cend(line); ++it) {
            // std::cout << *it << "\t";
            if (skip) {
                // std::cout << "skip\n";
                skip = false;
                continue;
            }
            if (*it == '!') {
                // std::cout << "mark skip\n";
                skip = true;
                continue;
            }
            if (garbage) {
                // std::cout << "garbage";
                if (*it == '>') {
                    // std::cout << " off";
                    garbage = false;
                }
                // std::cout << "\n";
                continue;
            }
            if (*it == '<') {
                // std::cout << "mark garbage\n";
                garbage = true;
                continue;
            }
            if (*it == '}') {
                // std::cout << "end group (level: " << level << ")\n";
                sum += level--;
                continue;
            }
            if (*it == '{') {
                ++level;
                // std::cout << "mark group (level: " << level << ")\n";
                continue;
            }
        }
        std::cout << "score : " << sum << "\n";
    }
}
