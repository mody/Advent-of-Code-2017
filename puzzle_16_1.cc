// Copyright (C) 2017, Seznam.cz, a.s.

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


std::string spin(std::string&& data, const std::string& cmd)
{
    std::string result;
    int count = atoi(&cmd[1]);
    auto middle = std::next(data.begin(), data.size()-count);
    std::copy(middle, data.end(), std::back_insert_iterator<std::string>(result));
    std::copy(data.begin(), middle, std::back_insert_iterator<std::string>(result));
    return result;
}

std::string swap_prog(std::string&& data, const std::string& cmd)
{
    auto _cmd = cmd;
    _cmd.erase(0, 1);
    std::vector<std::string> words;
    boost::algorithm::split(words, _cmd, boost::is_any_of("/"), boost::algorithm::token_compress_on);
    std::swap(data[atoi(words[0].c_str())], data[atoi(words[1].c_str())]);
    return data;
}

std::string swap_pos(std::string&& data, const std::string& cmd)
{
    std::swap(data[data.find(cmd[1])], data[data.find(cmd[3])]);
    return data;
}

int main()
{
    std::string data{"abcdefghijklmnop"};

    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> words;
    boost::algorithm::split(
        words, line, boost::is_any_of(","), boost::algorithm::token_compress_on);
    for (const auto& cmd : words) {
        if (cmd[0] == 's') {
            data = spin(std::move(data), cmd);
        } else if (cmd[0] == 'x') {
            data = swap_prog(std::move(data), cmd);
        } else if (cmd[0] == 'p') {
            data = swap_pos(std::move(data), cmd);
        } else {
            std::cerr << "ERROR: " << cmd << "\n";
            return 1;
        }
    }
    std::cout << "data: " << data << "\n";
    return 0;
}
