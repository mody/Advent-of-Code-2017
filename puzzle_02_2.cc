#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

int main() {
    std::string line;

    size_t checksum = 0;

    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }

        std::vector<int> nums;
        std::stringstream ss{line};
        while(!ss.eof()) {
            size_t x;
            ss >> x;
            nums.push_back(x);
        }

        for (int i = 0; i < nums.size(); ++i) {
            int a = nums[i];
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) {
                    continue;
                }
                int b = nums[j];
                int x = a/b;
                if (a == x*b) {
                    checksum += x;
                }
            }
        }
    }

    std::cout << "checksum: " << checksum << "\n";
}
