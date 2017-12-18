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
        int sum = 0;

        bool skip = false;
        bool garbage = false;

        for (auto it = std::cbegin(line); it != std::cend(line); ++it) {
            if (skip) {
                skip = false;
                continue;
            }
            if (*it == '!') {
                skip = true;
                continue;
            }
            if (garbage) {
                if (*it == '>') {
                    garbage = false;
                } else {
                    ++sum;
                }
                continue;
            }
            if (*it == '<') {
                garbage = true;
                continue;
            }
            if (*it == '}') {
                continue;
            }
            if (*it == '{') {
                continue;
            }
        }
        std::cout << "score : " << sum << "\n";
    }
}
