// Copyright (C) 2017, Seznam.cz, a.s.

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


struct Item
{
    std::string name;
    int weight;
    std::vector<std::string> children;
};

using Map = std::unordered_map<std::string, Item>;

int main()
{
    std::string line;

    Map map;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        std::vector<std::string> words;
        boost::algorithm::split(
            words, line, boost::is_any_of(" (),"), boost::algorithm::token_compress_on);

        Item me;
        me.name = words[0];
        me.weight = std::stoi(words[1]);
        if (words.size() > 3) {
            for (int i = 3; i < words.size(); ++i) {
                me.children.push_back(words[i]);
            }
        }
        map.insert({me.name, std::move(me)});
    }

    std::unordered_set<std::string> children;
    for (const auto& i : map) {
        for (const auto& c : i.second.children) {
            children.insert(c);
        }
    }

    for (const auto& i : map) {
        if (children.count(i.first)) {
            continue;
        }
        std::cout << i.first << "\n";
        break;
    }

    return 0;
}
