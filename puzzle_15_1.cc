// Copyright (C) 2017, Seznam.cz, a.s.

#include <iostream>
#include <limits>

int main()
{
    const unsigned long MULA = 16807;
    const unsigned long MULB = 48271;
    unsigned long genA = 722;
    unsigned long genB = 354;
    int same = 0;
    for (int i=0; i < 40000000; ++i) {
        genA = (genA * MULA) % 2147483647U;
        genB = (genB * MULB) % 2147483647U;

        if ((genA & 0xffff) == (genB & 0xffff)) {
            ++same;
        }
    }

    std::cout << "same: " << same << "\n";
    return 0;
}
