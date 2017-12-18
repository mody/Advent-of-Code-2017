#include <iostream>
#include <vector>

int main() {
    std::string line;
    std::vector<long> nums;

    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        nums.push_back(std::atoi(&line[0]));
    }

    size_t i = 0;
    for (size_t oldPos, pos = 0; pos < nums.size(); ++i) {
        oldPos = pos;
        pos += nums[pos];
        nums[oldPos]++;
    }

    std::cout << "escape in: " << i << "\n";
}
