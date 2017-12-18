#include <cmath>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>

struct Coord {
    int x = 0;
    int y = 0;

    bool operator== (const Coord& o) const {
        return x == o.x && y == o.y;
    }
};

struct pair_hash {
    size_t operator()(const Coord& c) const {
        size_t seed = 0;
        boost::hash_combine(seed, c.x);
        boost::hash_combine(seed, c.y);
        return seed;
    }
};
using Map = std::unordered_map<Coord, uint64_t, pair_hash>;
Map gMap;

void report(const Coord& c) {
    std::cout << "X: " << c.x << ", Y: " << c.y << ", V: " << gMap[c] << "\n";
}

uint64_t sumNeigh(const Coord& c) {
    static Coord null{0, 0};
    if (c == null) {
        return 1;
    }
    return gMap[{c.x, c.y + 1}]
         + gMap[{c.x, c.y - 1}]
         + gMap[{c.x + 1, c.y + 1}]
         + gMap[{c.x + 1, c.y - 1}]
         + gMap[{c.x - 1, c.y + 1}]
         + gMap[{c.x - 1, c.y - 1}]
         + gMap[{c.x - 1, c.y}]
         + gMap[{c.x + 1, c.y}];
}

void Spiral(int X, int Y, int target) {
    int x, y, dx, dy;
    x = y = dx = 0;
    dy         = -1;
    int t      = std::max(X, Y);
    int maxI   = t * t;
    for (int i = 0; i < maxI; i++) {
        if ((-X / 2 <= x) && (x <= X / 2) && (-Y / 2 <= y) && (y <= Y / 2)) {
            Coord c{x, y};
            auto V = gMap[c] = sumNeigh(c);
            if (V > target) {
                report(c);
                return;
            }
        }
        if ((x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1 - y))) {
            t  = dx;
            dx = -dy;
            dy = t;
        }
        x += dx;
        y += dy;
    }
}

int main() {
    std::vector<int> inputs{325489};
    for (auto n : inputs) {
        std::cout << "input: " << n << "; ";
        Spiral(800, 800, n);
    }
}
