// Copyright (C) 2017, Seznam.cz, a.s.

#include <algorithm>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <array>
#include <string>

const unsigned NUMS = 256;

int main() {
    std::vector<int> lengths;

    std::string line;
    std::getline(std::cin, line);

    std::vector<std::string> words;
    boost::algorithm::split(
            words, line, boost::is_any_of(", "), boost::algorithm::token_compress_on);
    for (const auto& w : words) {
        lengths.push_back(std::stoi(&w[0]));
    }

    std::array<int, NUMS> nums;
    for (unsigned i = 0; i < NUMS; ++i) {
        nums[i] = i;
    }

    int skip = 0;
    int pos = 0;

    for (auto w : lengths) {
        int from = pos, to = (pos + w - 1) % NUMS;
        for(unsigned i = w/2; i > 0; --i) {
            std::swap(nums[from], nums[to]);
            from = ++from % NUMS;
            if (to == 0) {
                to = NUMS;
            }
            to = --to;
        }
        pos = (pos + w + skip++) % NUMS;
    }

    std::cout << "0: " << nums[0] << "\n"
    << "1: " << nums[1] << "\n"
    << "multiple: " << nums[0]*nums[1] << "\n";
}
