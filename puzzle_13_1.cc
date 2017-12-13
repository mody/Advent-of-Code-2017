// Copyright (C) 2017, Seznam.cz, a.s.

#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

struct Layer {
    int range = 0;
    int scanner_pos = 0;
    int scanner_dir = 1;

    void move_scanner() {
        if (scanner_pos == 0) {
            scanner_dir = 1;
        } else if (scanner_pos == range-1) {
            scanner_dir = -1;
        }
        scanner_pos += scanner_dir;
    }
};

using Map = std::map<int, Layer>;

int main()
{
    Map map;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> words;
        boost::algorithm::split(
                words, line, boost::is_any_of(": "), boost::algorithm::token_compress_on);

        int k = std::stoi(&words[0][0]);
        int r = std::stoi(&words[1][0]);
        map[k] = Layer{r};
    }

    int severity = 0;
    for (int pos = 0; pos <= map.rbegin()->first; ++pos) {
        auto it = map.find(pos);
        if (it != map.end()) {
            if (it->second.scanner_pos == 0) {
                severity += (pos*it->second.range);
            }
        }
        for (auto& l : map) {
            l.second.move_scanner();
        }
    }

    std::cout << "severity: " << severity << "\n";
    return 0;
}
