#include <iostream>
#include <limits>

int main()
{
    const unsigned long MULA = 16807;
    const unsigned long MULB = 48271;
    unsigned long genA = 722;
    unsigned long genB = 354;
    int same = 0;

    for (int i=0; i < 5000000; ) {
        for(;;) {
            genA = (genA * MULA) % 2147483647U;
            if (((genA / 4) * 4) == genA) {
                break;
            }
        }
        for(;;) {
            genB = (genB * MULB) % 2147483647U;
            if (((genB / 8) * 8) == genB) {
                break;
            }
        }

        if ((genA & 0xffff) == (genB & 0xffff)) {
            ++same;
        }
        ++i;
    }

    std::cout << "same: " << same << "\n";
    return 0;
}
