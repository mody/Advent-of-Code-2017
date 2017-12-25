#include <iostream>
#include <set>

const int MIDDLE = 12261543;
using Tape = std::set<int>;

Tape tape;

int main()
{
    unsigned char state = 'A';
    int pos = 0;

    for (int i = 0; i < MIDDLE; ++i) {
        auto it = tape.find(pos);
        switch (state) {
            // Begin in state A.
            // Perform a diagnostic checksum after 12261543 steps.

        case 'A':
            if (it == tape.end()) {
                tape.insert(pos);
                ++pos;
                state = 'B';
            } else {
                tape.erase(pos);
                --pos;
                state = 'C';
            }
            break;

        case 'B':
            if (it == tape.end()) {
                tape.insert(pos);
                --pos;
                state = 'A';
            } else {
                tape.insert(pos);
                ++pos;
                state = 'C';
            }
            break;

        case 'C':
            if (it == tape.end()) {
                tape.insert(pos);
                ++pos;
                state = 'A';
            } else {
                tape.erase(pos);
                --pos;
                state = 'D';
            }
            break;

        case 'D':
            if (it == tape.end()) {
                tape.insert(pos);
                --pos;
                state = 'E';
            } else {
                tape.insert(pos);
                --pos;
                state = 'C';
            }
            break;

        case 'E':
            if (it == tape.end()) {
                tape.insert(pos);
                ++pos;
                state = 'F';
            } else {
                tape.insert(pos);
                ++pos;
                state = 'A';
            }
            break;

        case 'F':
            if (it == tape.end()) {
                tape.insert(pos);
                ++pos;
                state = 'A';
            } else {
                tape.insert(pos);
                ++pos;
                state = 'E';
            }
            break;
        }
    }

    std::cout << tape.size() << "\n";

    return 0;
}
