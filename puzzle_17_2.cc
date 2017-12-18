#include <iostream>

constexpr int STEPS = 376;
constexpr int ITERATIONS = 50000001;

int main()
{
    int answer_pt2 = 0;

    for (int i = 1, idx = 0; i < ITERATIONS; i++) {
        idx = (idx + 1 + STEPS) % i;
        if (idx == 0) answer_pt2 = i;
    }

    std::cout << answer_pt2 << std::endl;

    return 0;
}
