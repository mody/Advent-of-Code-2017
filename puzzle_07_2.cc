#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Children = std::unordered_map<std::string, int>;

struct Item
{
    std::string name;
    int weight = 0;
    int sumweight = 0;
    Children children;
};

using Map = std::unordered_map<std::string, Item>;

int fillSumWeight(Map& map, const std::string &name) {
    Item& me = map.at(name);
    for (auto& child : me.children) {
        child.second = fillSumWeight(map, child.first);
        me.sumweight += child.second;
    }
    if (!std::all_of(me.children.begin(), me.children.end(), [&](const auto& it) {
            return it.second == me.children.begin()->second;
        }))
    {
        std::cout << "FAILS: " << me.name << "\n";
        for (const auto& it : me.children) {
            std::cout << "\t" << it.first << ", sum: " << it.second
                      << ", own: " << map.at(it.first).weight << "\n";
        }
    }
    return me.sumweight + me.weight;
}

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
                me.children.insert({words[i], 0});
            }
        }
        map.insert({me.name, std::move(me)});
    }

    std::unordered_set<std::string> children;
    for (const auto& i : map) {
        for (const auto& c : i.second.children) {
            children.insert(c.first);
        }
    }

    std::string topName;
    for (const auto& i : map) {
        if (children.count(i.first)) {
            continue;
        }
        topName = i.first;
        break;
    }

    fillSumWeight(map, topName);
    std::cout << "\n";
    return 0;
}
