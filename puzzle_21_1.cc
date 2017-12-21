#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <map>
#include <vector>

using StringVect = std::vector<std::string>;

std::map<std::string, std::string> rules;

void show(const StringVect& v)
{
    for (const auto& r : v) {
        std::cout << r << "\n";
    }
    std::cout << "-----------------\n";
}

void mixRules2(const std::string& a, const std::string& b)
{
    StringVect rows;
    boost::algorithm::split(rows, a, boost::is_any_of("/"), boost::algorithm::token_compress_on);

    // orig
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // left-right
    for (auto& r : rows) {
        std::reverse(r.begin(), r.end());
    }
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // top-down
    std::swap(rows[0], rows[1]);
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // left-right
    for (auto& r : rows) {
        std::reverse(r.begin(), r.end());
    }
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // rotate
    std::swap(rows[0][0], rows[1][1]);
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // top-down
    std::swap(rows[0], rows[1]);
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // left-right
    for (auto& r : rows) {
        std::reverse(r.begin(), r.end());
    }
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // std::cout << "============\n";
}

void mixRules3(std::string a, const std::string& b)
{
    StringVect rows;
    boost::algorithm::split(rows, a, boost::is_any_of("/"), boost::algorithm::token_compress_on);

    // orig
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // left-right
    for (auto& r : rows) {
        std::reverse(r.begin(), r.end());
    }
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // top-down
    std::swap(rows[0], rows[2]);
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // left-right
    for (auto& r : rows) {
        std::reverse(r.begin(), r.end());
    }
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // rotate
    std::swap(rows[0][1], rows[1][0]);
    std::swap(rows[0][2], rows[2][0]);
    std::swap(rows[1][2], rows[2][1]);
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // top-down
    std::swap(rows[0], rows[2]);
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});

    // left-right
    for (auto& r : rows) {
        std::reverse(r.begin(), r.end());
    }
    // show(rows);
    rules.insert({boost::algorithm::join(rows, "/"), b});
}


int main()
{
    std::string line;
    while (getline(std::cin, line)) {
        StringVect words;
        boost::algorithm::split(
            words, line, boost::is_any_of("\t"), boost::algorithm::token_compress_on);
        if (words[0].size() == 5) {
            mixRules2(words[0], words[1]);
        } else {
            mixRules3(words[0], words[1]);
        }
    }

    StringVect map{{".#."}, {"..#"}, {"###"}};

    for (int ll = 0; ll < 5; ++ll) {
        if ((map.size() / 2) * 2 == map[0].size()) {
            std::cout << "dvema\n";
            StringVect newMap;
            int ny = 0;
            int x = 0;
            int y = 0;
            for (;;) {
                std::string k;
                const auto& row0 = map[y];
                const auto& row1 = map[y + 1];
                k.push_back(row0[x]);
                k.push_back(row0[x + 1]);
                k.push_back('/');
                k.push_back(row1[x]);
                k.push_back(row1[x + 1]);

                auto it = rules.find(k);
                if (it != rules.end()) {
                    StringVect rows;
                    boost::algorithm::split(
                        rows, it->second, boost::is_any_of("/"),
                        boost::algorithm::token_compress_on);
                    if (newMap.size() < ny + 3) {
                        newMap.resize(ny + 3);
                    }
                    newMap[ny].append(rows[0]);
                    newMap[ny + 1].append(rows[1]);
                    newMap[ny + 2].append(rows[2]);
                } else {
                    std::cerr << "NOT FOUND! r: " << y << ", c: " << x << "\n";
                }
                x += 2;
                if (x == row0.size()) {
                    x = 0;
                    y += 2;
                    ny += 3;
                }
                if (y == map.size()) {
                    break;
                }
            }
            std::swap(newMap, map);
        } else if ((map[0].size() / 3) * 3 == map[0].size()) {
            std::cout << "trema\n";
            StringVect newMap;
            int ny = 0;
            int x = 0;
            int y = 0;
            for (;;) {
                std::string k;
                const auto& row0 = map[y];
                const auto& row1 = map[y + 1];
                const auto& row2 = map[y + 2];
                k.push_back(row0[x]);
                k.push_back(row0[x + 1]);
                k.push_back(row0[x + 2]);
                k.push_back('/');
                k.push_back(row1[x]);
                k.push_back(row1[x + 1]);
                k.push_back(row1[x + 2]);
                k.push_back('/');
                k.push_back(row2[x]);
                k.push_back(row2[x + 1]);
                k.push_back(row2[x + 2]);

                auto it = rules.find(k);
                if (it != rules.end()) {
                    StringVect rows;
                    boost::algorithm::split(
                        rows, it->second, boost::is_any_of("/"),
                        boost::algorithm::token_compress_on);
                    if (newMap.size() < ny + 4) {
                        newMap.resize(ny + 4);
                    }
                    newMap[ny].append(rows[0]);
                    newMap[ny + 1].append(rows[1]);
                    newMap[ny + 2].append(rows[2]);
                    newMap[ny + 3].append(rows[3]);
                } else {
                    std::cerr << "NOT FOUND! r: " << y << ", c: " << x << "\n";
                }
                x += 3;
                if (x == row0.size()) {
                    x = 0;
                    y += 3;
                    ny += 4;
                }
                if (y == map.size()) {
                    break;
                }
            }
            std::swap(newMap, map);
        } else {
            std::cerr << "ERROR! " << map[0].size();
        }

        show(map);
    }

    int cnt = 0;
    for (const auto& r : map) {
        cnt += std::count_if(r.begin(), r.end(), [](const unsigned char c) { return c == '#'; });
    }
    std::cout << "cnt: " << cnt << "\n";

    return 0;
}
