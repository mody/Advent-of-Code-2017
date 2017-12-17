// Copyright (C) 2017, Seznam.cz, a.s.

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <list>

constexpr int STEPS = 376;

int main()
{
    std::list<int> data;
    data.push_back(0);

    auto pos = data.begin();
    for (int i=1; i < 2018; ++i) {
        pos = std::next(data.begin(), (std::distance(data.begin(), pos) + STEPS) % data.size());
        pos = data.insert(++pos, i);
    }
    std::cout << "current: " << *pos << "\n"
        << "next: " << *++pos << "\n";
    return 0;
}
