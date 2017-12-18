#include <iostream>
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iterator>
#include <vector>
#include <unordered_set>

int main() {
    std::string line;
    size_t correct = 0;

    while(std::getline(std::cin, line)) {
        if (line.empty()) {
            break;
        }

        std::vector<std::string> words;
        boost::algorithm::split(words, line, boost::is_any_of(" "), boost::algorithm::token_compress_on);

        std::unordered_set<std::string> set;

        std::transform(std::cbegin(words), std::cend(words),
                  std::insert_iterator<std::unordered_set<std::string>>(set, set.begin()),
                  [](const std::string& w) -> std::string {
                    std::string tmp{w};
                    std::sort(tmp.begin(), tmp.end());
                    return tmp;
                  });

        if (words.size() == set.size()) {
            ++correct;
        }
    }
    std::cout << "correct: " << correct << "\n";
}
