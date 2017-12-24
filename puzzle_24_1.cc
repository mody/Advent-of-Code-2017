#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <assert.h>
#include <set>

struct Port {
    int a = 0, b = 0;
    int used = 0;

    bool operator< (const Port& rhs) const {
        return std::tie(a, b) < std::tie(rhs.a, rhs.b);
    }

    bool operator== (const Port& rhs) const {
        return std::tie(a, b, used) == std::tie(rhs.a, rhs.b, rhs.used);
    }
};

using Ports = std::vector<Port>;

void longest(Ports& ports, const int id, const int sum, const std::string msg) {
    // auto end = std::partition(ports.begin(), ports.end(), [](const Port& p) { return !p.used; });
    Ports::iterator it = ports.begin();
    if (it == ports.end()) {
        std::cout << sum  << " - end1\n";
        return;
    }
    std::set<Port> used;
    for(;;) {
        // std::sort(ports.begin(), end);
        auto it = std::find_if(ports.begin(), ports.end(), [&id, &used](const Port& p) {
            return (p.a == id || p.b == id) && used.insert(p).second;
        });
        if (it == ports.end()) {
            // std::cout << msg << " = ";
            // std::cout << sum << " - end2\n";
            break;
        }
        // for (auto ii = ports.begin(); ii != ports.end(); ++ii) {
        //     if (ii == it) {
        //         std::cout << "(";
        //     } else if (ii == end) {
        //         std::cout << "[";
        //     }
        //     std::cout << ii->a << "/" << ii->b << "/" << ii->used;
        //     if (ii == it) {
        //         std::cout << ")";
        //     } else if (ii == end) {
        //         std::cout << "]";
        //     }
        //     std::cout << ",";
        // }
        // std::cout << "\n";

        Port bck{*it};
        ports.erase(it);
        int newId = bck.a == id ? bck.b : bck.a;
        // std::cout << bck.a << "/" << bck.b << "--";
        longest(
            ports, newId, sum + bck.a + bck.b,
            msg + "--" + std::to_string(bck.a) + "/" + std::to_string(bck.b));

        // it = find(ports.begin(), ports.end(), bck);
        // assert(it != end);
        // it->used = 0;
        ports.emplace_back(std::move(bck));
    }
    // std::cout << msg << " = ";
    std::cout << sum << " - end2\n";
}

int main()
{
    Ports ports;

    std::string line;
    while(getline(std::cin, line)) {
        Port p;
        p.a = atoi(&line[0]);
        p.b = atoi(&line[line.find('/')+1]);
        ports.emplace_back(std::move(p));
    }

    longest(ports, 0, 0, "");

    return 0;
}
