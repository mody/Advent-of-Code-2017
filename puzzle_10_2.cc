// Copyright (C) 2017, Seznam.cz, a.s.

#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const unsigned NUMS = 256;

int main() {
    std::vector<unsigned> lengths;

    std::string line;
    std::getline(std::cin, line);

    for (const unsigned& c : line) {
        lengths.push_back(c);
    }
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);

    std::array<unsigned char, NUMS> nums;
    for (unsigned i = 0; i < NUMS; ++i) {
        nums[i] = i;
    }

    int skip = 0;
    int pos = 0;

    for (unsigned round = 0; round < 64; ++round) {
        for (auto w : lengths) {
            int from = pos, to = (pos + w - 1) % NUMS;
            for (unsigned i = w / 2; i > 0; --i) {
                std::swap(nums[from], nums[to]);
                from = ++from % NUMS;
                if (to == 0) {
                    to = NUMS;
                }
                to -= 1;
            }
            pos = (pos + w + skip++) % NUMS;
        }
    }

    std::array<unsigned, 16> dense;
    for (int i=0; i<16; ++i) {
        int from = 16*i;
        int to = 16*(i+1);
        unsigned char h = nums[from];
        for (++from; from < to; ++from) {
            h ^= nums[from];
        }
        dense[i] = h;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned)h;
    }
    std::cout << "\n";
}
