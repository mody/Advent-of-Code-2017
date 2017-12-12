// Copyright (C) 2017, Seznam.cz, a.s.

#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

using Children = std::vector<int>;
using Map = std::map<int, Children>;

int main()
{
    Map map;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> words;
        boost::algorithm::split(
                words, line, boost::is_any_of(", "), boost::algorithm::token_compress_on);

        auto it = words.begin();
        int k = std::stoi(&(*it++)[0]);

        if (*it++ != "<->") {
            std::cerr << "ERROR: " << line << "\n";
            return 1;
        }

        for (; it != words.end(); ++it) {
            map[k].push_back(std::stoi(&(*it)[0]));
        }
    }

    std::list<int> queue;
    queue.push_back(0);
    std::set<int> zero_group;
    zero_group.insert(0);

    for(;!queue.empty();) {
        int cur = queue.front();
        queue.pop_front();
        const auto& next = map[cur];
        for (auto i : next) {
            if (zero_group.insert(i).second) {
                queue.push_back(i);
            }
        }
    }

    std::cout << "zero_group: " << zero_group.size() << "\n";
}
