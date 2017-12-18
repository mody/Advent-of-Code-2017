#include <cmath>
#include <iostream>
#include <vector>

void report(int x, int y) {
    std::cout << "X: " << x << ", Y: " << y << "; steps: " << (std::abs(x) + std::abs(y))
              << "\n";
}

void Spiral(int X, int Y, int target) {
    int x, y, dx, dy;
    x = y = dx = 0;
    dy         = -1;
    int t      = std::max(X, Y);
    int maxI   = t * t;
    for (int i = 0; i < maxI; i++) {
        if ((-X / 2 <= x) && (x <= X / 2) && (-Y / 2 <= y) && (y <= Y / 2)) {
           if (i == target-1) {
               report(x, y);
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
    std::vector<int> inputs{1, 12, 23, 1024, 325489};
    for (auto n : inputs) {
        std::cout << "input: " << n << "; ";
        Spiral(1000, 1000, n);
    }
}
