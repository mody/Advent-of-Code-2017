// Copyright (C) 2017, Seznam.cz, a.s.

#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <string>

enum {
    DIR_N = 1,
    DIR_S,
    DIR_NW,
    DIR_NE,
    DIR_SW,
    DIR_SE
};

static int toDir(const std::string& dir) {
    if (dir == "n") {
        return DIR_N;
    } else if (dir == "s") {
        return DIR_S;
    } else if (dir == "nw") {
        return DIR_NW;
    } else if (dir == "ne") {
        return DIR_NE;
    } else if (dir == "sw") {
        return DIR_SW;
    } else if (dir == "se") {
        return DIR_SE;
    } else {
        std::cerr << "WRONG MOVE!\n";
        exit(1);
    }
};

struct Position
{
    int x = 0;
    int y = 0;
    int z = 0;
    int dist = 0;

    void move(const int dir)
    {
        if (dir == DIR_N) {
            y += 1;
            z -= 1;
        } else if (dir == DIR_S) {
            y -= 1;
            z += 1;
        } else if (dir == DIR_NW) {
            x -= 1;
            y += 1;
        } else if (dir == DIR_NE) {
            x += 1;
            z -= 1;
        } else if (dir == DIR_SW) {
            x -= 1;
            z += 1;
        } else if (dir == DIR_SE) {
            x += 1;
            y -= 1;
        }
        dist = (std::abs(x)+std::abs(y)+std::abs(z)) / 2;
    }
};


int main()
{
    std::string line;
    std::getline(std::cin, line);

    std::vector<float> path;
    Position child;
    {
        std::vector<std::string> words;
        boost::algorithm::split(
            words, line, boost::is_any_of(", "), boost::algorithm::token_compress_on);
        for (const auto& dir : words) {
            child.move(toDir(dir));
            path.push_back(child.dist);
        }
    }

    std::cout << "child dist: " << *path.rbegin() << "\n";
    std::sort(path.begin(), path.end(), std::greater<int>());
    std::cout << "max dist: " << path[0] << "\n";

    return 0;
}
