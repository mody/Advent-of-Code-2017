#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Registers = std::unordered_map<std::string, int>;

Registers reg;
int mm = 0;

int& getReg(const std::string& name) {
    return reg.insert({name, 0}).first->second;
}

bool eval_cond(const std::vector<std::string>& words)
{
    if (words[3] == "if") {
        int& r = getReg(words[4]);
        int val = stoi(words[6]);
        std::cout << ", CR: " << words[4] << ", op: " << words[5] << ", val: " << val;
        if (words[5] == "==") {
            return r == val;
        } else if (words[5] == ">=") {
            return r >= val;
        } else if (words[5] == "<=") {
            return r <= val;
        } else if (words[5] == "!=") {
            return r != val;
        } else if (words[5] == ">") {
            return r > val;
        } else if (words[5] == "<") {
            return r < val;
        } else {
            std::cerr << "UNKNOWN CONDITIONAL OP: " << words[5] << "\n";
            exit(1);
        }
    } else {
        std::cerr << "UNKNOWN CONDITIONAL: " << words[3] << "\n";
        exit(1);
    }
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }
        std::vector<std::string> words;
        boost::algorithm::split(
            words, line, boost::is_any_of(" "), boost::algorithm::token_compress_on);

        int& r = getReg(words[0]);
        int val = stoi(words[2]);

        std::cout << "R: " << words[0] << ", op: " << words[1] << ", val: " << val;
        if (words.size() > 3 && !eval_cond(words)) {
            std::cout << " skip\n";
            continue;
        }

        if (words[1] == "inc") {
            std::cout << ", INC\n";
            r += val;
        } else if (words[1] == "dec") {
            std::cout << ", DEC\n";
            r -= val;
        } else {
            std::cerr << "UNKNOWN OP: " << words[1] << "\n";
            exit(1);
        }
        mm = std::max(mm, r);
    }

    auto m = std::max_element(
        reg.begin(), reg.end(), [](const Registers::value_type& a, const Registers::value_type& b) {
            return std::less<int>()(a.second, b.second);
        });

    std::cout << "max: " << m->second << ", mm: " << mm << "\n";
    return 0;
}
