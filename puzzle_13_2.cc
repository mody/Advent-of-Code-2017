#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <vector>


struct Layer
{
    int range = 0;
    std::vector<int> positions;

    Layer(int r)
        : range(r)
    {
        for (int i = 0; i < r; ++i) {
            positions.push_back(i);
        }
        for (int i = range - 2; i > 0; --i) {
            positions.push_back(i);
        }
    }

    int scanner_pos(int tick) const
    {
        return positions[tick % positions.size()];
    }
};

using Map = std::map<int, Layer>;

int main()
{
    Map map;

    std::string line;
    int max_k = 0;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> words;
        boost::algorithm::split(
                words, line, boost::is_any_of(": "), boost::algorithm::token_compress_on);

        int k = std::stoi(&words[0][0]);
        int r = std::stoi(&words[1][0]);
        map.insert({k, Layer{r}});
        max_k = std::max(max_k, k);
    }

    int delay = 0;
    for (;;++delay) {
        bool hit = false;
        for (int pos = 0; pos <= max_k; ++pos) {
            int tick = delay + pos;
            auto it = map.find(pos);
            if (it != map.end()) {
                if (it->second.scanner_pos(tick) == 0) {
                    hit = true;
                    break;
                }
            }
        }
        if (!hit) {
            break;
        }
    }

    std::cout << "delay: " << delay << "\n";

    return 0;
}
