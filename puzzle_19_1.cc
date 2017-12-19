#include <iostream>
#include <array>
#include <vector>

enum { NONE, UP, DOWN, LEFT, RIGHT };

std::vector<std::string> map;


bool isValidPos(int row, int pos) {
    if (row < 0 || pos < 0 || row >= map.size() || pos >= map[row].size()) {
        return false;
    }
    return true;
}

bool makeMove(int& row, int& pos, int mv)
{
    switch (mv) {
    case DOWN: ++row; break;
    case UP: --row; break;
    case LEFT: --pos; break;
    case RIGHT: ++pos; break;
    case NONE: exit(1);
    }
    return isValidPos(row, pos);
}

bool isValidMove(int row, int pos, int mv) {
    makeMove(row, pos, mv);
    return isValidPos(row, pos);
}

std::array<int, 3> availMoves(int mv)
{
    switch (mv) {
    case DOWN:
    case UP: return {{LEFT, RIGHT}};
    case LEFT:
    case RIGHT: return {{UP, DOWN}};
    }
    return {};
}

int main() {
    std::string line;
    while(std::getline(std::cin, line)) {
        map.emplace_back(std::move(line));
    }

    std::string chars;
    int row = 0;
    int pos = map[row].find("|");
    int mv = DOWN;

    for (;;) {
        if (!makeMove(row, pos, mv) || map[row][pos] == ' ') {
            break;
        }
        // std::cout << row << "; " << pos << " - " << (unsigned char)map[row][pos] << "\n";
        if (map[row][pos] == '|') {
            continue;
        } else if (map[row][pos] == '-') {
            continue;
        } else if (map[row][pos] == '+') {
            for (auto _mv : availMoves(mv)) {
                int _row = row;
                int _pos = pos;
                // std::cout << "oldMv: " << mv << ", tryMv: " << _mv << " - ";
                if (makeMove(_row, _pos, _mv) && map[_row][_pos] != ' ') {
                    // std::cout << "Ok\n";
                    mv = _mv;
                    break;
                }
                // std::cout << "\n";
            }
            // which way?
        } else {
            chars.push_back(map[row][pos]);
        }
    }

    std::cout << "chars: " << chars << "\n";

    return 0;
}
