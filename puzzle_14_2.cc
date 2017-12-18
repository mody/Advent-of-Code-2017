#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

const unsigned NUMS = 256;

std::array<std::array<int, 128>, 128> map;

void mark_group(int r, int c, int group)
{
    if (map[r][c] != -1) {
        return;
    }
    map[r][c] = group;

    if (c && map[r][c-1] == -1) {
        mark_group(r, c-1, group);
    }
    if (r && map[r-1][c] == -1) {
        mark_group(r-1, c, group);
    }
    if (c < 127 && map[r][c+1] == -1) {
        mark_group(r,c +1, group);
    }
    if (r <127 && map[r+1][c] == -1) {
        mark_group(r+1, c, group);
    }
}

int main() {

    int row = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<unsigned> input;
        for (const unsigned& c : line) {
            input.push_back(c);
        }
        input.push_back(17);
        input.push_back(31);
        input.push_back(73);
        input.push_back(47);
        input.push_back(23);

        std::array<unsigned char, NUMS> nums;
        for (unsigned i = 0; i < NUMS; ++i) {
            nums[i] = i;
        }

        int skip = 0;
        int pos = 0;

        for (unsigned round = 0; round < 64; ++round) {
            for (auto w : input) {
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

        for (int i = 0; i < 16; ++i) {
            int from = 16 * i;
            int to = 16 * (i + 1);
            unsigned char h = nums[from];
            for (++from; from < to; ++from) {
                h ^= nums[from];
            }
            for(int b = 0; b < 8; ++b) {
                map[row][8*i+(7-b)] = (h & 0x1) ? -1 : 0;
                h >>= 1;
            }
        }
        ++row;
    }

    int group = 0;
    for (int r = 0; r < map.size(); ++r) {
        auto& row = map[r];
        for (int c = 0; c < row.size(); ++c) {
            if (row[c] == -1) {
                ++group;
            }
            mark_group(r, c, group);
        }
    }

    std::cerr << "group: " << group << "\n";
    return 0;
}
