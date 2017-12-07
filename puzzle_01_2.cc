// Copyright (C) 2017, Seznam.cz, a.s.

#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::string line;
    std::cin >> line;

    if (line.empty()) {
        std::cout << "0\n";
        return 0;
    }

    const unsigned size = line.size();
    const unsigned half = size/2;

    for (unsigned i = 0; i < half; ++i) {
        line.push_back(line[i]);
    }

    unsigned sum = 0;

    for (int i = 0; i < size; ++i) {
        const unsigned c = line[i];
        if (c == line[half + i]) {
            sum += c - '0';
        }
    }
    std::cout << sum << "\n";
}
