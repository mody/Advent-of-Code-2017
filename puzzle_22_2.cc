#include <iostream>
#include <string>
#include <map>
#include <tuple>

enum State { CLEAN, WEAKENED, INFECTED, FLAGGED, _END_STATE };

struct Point {
    int x = 0, y = 0;

    bool operator< (const Point& rhs) const {
        return std::tie(x, y) < std::tie(rhs.x, rhs.y);
    }
};

using Map = std::map<Point, State>;

int main() {
    Map map;

    Point p;
    int max_x = 0, max_y = 0;
    std::string line;
    while(getline(std::cin, line)) {
        for (unsigned char c : line) {
            if (c == '#') {
                map.insert({p, INFECTED});
            }
            ++p.x;
        }
        max_x = std::max(max_x, p.x);
        ++p.y;
        p.x = 0;
    };
    max_y = p.y;

    p = Point{max_x/2, max_y/2};

    std::cout << "max_x: " << max_x << ", max_y: " << max_y << "\n";
    std::cout << "x: " << p.x << ", y: " << p.y << "\n";

    enum DIR { UP, RIGHT, DOWN, LEFT, _DIR_SIZE };

    int infected = 0;
    DIR dir = DIR::UP;
    for (int i = 0; i < 10000000; ++i) {
        auto current_infected = map.find(p);
        if (current_infected == map.end()) {
            // clean
            dir = (DIR)((dir - 1 + _DIR_SIZE) % _DIR_SIZE);
            map.insert({p, WEAKENED});
        } else if (current_infected->second == WEAKENED) {
            current_infected->second = INFECTED;
            ++infected;
        } else if (current_infected->second == INFECTED) {
            current_infected->second = FLAGGED;
            dir = (DIR)((dir + 1) % _DIR_SIZE);
        } else if (current_infected->second == FLAGGED) {
            map.erase(current_infected);
            dir = (DIR)((dir + 2) % _DIR_SIZE);
        }
        switch (dir) {
        case UP: --p.y; break;
        case DOWN: ++p.y; break;
        case RIGHT: ++p.x; break;
        case LEFT: --p.x; break;
        default: std::cerr << "ERROR! "<< dir << "\n"; break;
        }
    }

    std::cout << "infected: " << infected << "\n";
    return 0;
}
