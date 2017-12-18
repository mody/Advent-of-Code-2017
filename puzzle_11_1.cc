#include <algorithm>
#include <array>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <unordered_map>

struct Position
{
    int x = 0;
    int y = 0;

    bool operator== (const Position& o) const {
        return std::tie(x, y) == std::tie(o.x, o.y);
    }

    void move(const std::string& dir)
    {
        if (y & 1) {
            // lichy radek
            if (dir == "n") {
                y -= 2;
            } else if (dir == "s") {
                y += 2;
            } else if (dir == "nw") {
                y -= 1;
            } else if (dir == "ne") {
                y -= 1;
                x += 1;
            } else if (dir == "sw") {
                y += 1;
            } else if (dir == "se") {
                y += 1;
                x += 1;
            } else {
                std::cerr << "WRONG MOVE!\n";
                exit(1);
            }
        } else {
            // sudy radek
            if (dir == "n") {
                y -= 2;
            } else if (dir == "s") {
                y += 2;
            } else if (dir == "nw") {
                y -= 1;
                x -= 1;
            } else if (dir == "ne") {
                y -= 1;
            } else if (dir == "sw") {
                y += 1;
                x -= 1;
            } else if (dir == "se") {
                y += 1;
            } else {
                std::cerr << "WRONG MOVE!\n";
                exit(1);
            }
        }
    }
};


namespace std {

template<>
struct hash<Position>
{
    using argument_type = Position;
    using result_type = std::size_t;

    result_type operator()(argument_type const& pos) const noexcept
    {
        size_t seed = 0;
        boost::hash_combine(seed, pos.x);
        boost::hash_combine(seed, pos.y);
        return seed;
    }
};

}  // namespace std


int main()
{
    std::string line;
    std::getline(std::cin, line);

    std::vector<std::string> moves;
    boost::algorithm::split(
        moves, line, boost::is_any_of(", "), boost::algorithm::token_compress_on);

    Position child;
    for (const std::string& move : moves) {
        child.move(move);
    }

    std::unordered_map<Position, int> positions;
    std::list<const Position*> queue;

    auto x = positions.insert({Position{}, 0});
    queue.emplace_back(&(x.first->first));

    for (;!queue.empty();) {
        const auto cur = positions.find(*queue.front());
        assert(cur != positions.end());

        if (cur->first == child) {
            std::cout << "STEPS: " << cur->second << "\n";
            break;
        }
        queue.pop_front();

        for (const auto& dir : {"n", "s", "nw", "ne", "sw", "se"}) {
            Position _p = cur->first;
            _p.move(dir);
            int nextStep = cur->second + 1;
            auto it = positions.insert({_p, nextStep});
            if (it.second) {
                queue.emplace_back(&(it.first->first));
            } else if (it.first->second > nextStep) {
                it.first->second = nextStep;
            }
        }

    }

    return 0;
}
