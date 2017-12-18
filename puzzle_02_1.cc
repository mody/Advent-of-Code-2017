#include <iostream>
#include <sstream>
#include <limits>

int main() {
    std::string line;

    size_t checksum = 0;

    while(std::getline(std::cin, line)) {
        // std::cout << "line: " << line << "\n";

        if (line.empty()) {
            break;
        }

        size_t min = std::numeric_limits<size_t>::max(), max = std::numeric_limits<size_t>::min();
        std::stringstream ss{line};
        while(ss) {
            size_t x;
            ss >> x;
            // std::cout << "x: " << x << "\n";
            if (x < min) {
                min = x;
            }
            if (x > max) {
                max = x;
            }
        }
        checksum += (max - min);
    }

    std::cout << "checksum: " << checksum << "\n";
}
