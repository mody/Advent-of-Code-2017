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

    line.push_back(line[0]);

    unsigned sum = 0;
    for (int i = 0; i < size; ++i) {
        const unsigned c = line[i];
        if (c == line[1 + i]) {
            sum += c - '0';
        }
    }
    std::cout << sum << "\n";
}
