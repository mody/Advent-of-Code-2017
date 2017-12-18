// Copyright (C) 2017, Seznam.cz, a.s.

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// snd X plays a sound with a frequency equal to the value of X.
// set X Y sets register X to the value of Y.
// add X Y increases register X by the value of Y.
// mul X Y sets register X to the result of multiplying the value contained in
//  register X by the value of Y.
// mod X Y sets register X to the remainder of dividing the value contained in
//  register X by the value of Y (that is, it sets X to the result of X modulo Y).
// rcv X recovers the frequency of the last sound played, but only when the
//  value of X is not zero. (If it is zero, the command does nothing.)
// jgz X Y jumps with an offset of the value of Y, but only if the value of X
//  is greater than zero. (An offset of 2 skips the next instruction, an offset
//  of -1 jumps to the previous instruction, and so on.)

using Registers = std::map<std::string, long>;
Registers registers;

Registers::iterator regOrVal(const std::string& input)
{
    // std::cout << "input: " << input << " is ";
    if (input[0] == '-' || (input[0] >= '0' && input[0] <= '9')) {
        auto it = registers.insert({input, atoi(&input[0])}).first;
        // std::cout << "val: " << it->second << "\n";
        return it;
    } else {
        auto it = registers.insert({input, 0}).first;
        // std::cout << "reg: " << it->second << "\n";
        return it;
    }
}


int main()
{
    std::vector<std::string> program;

    std::string line;
    while (std::getline(std::cin, line)) {
        program.emplace_back(std::move(line));
    }

    int ip = 0;
    int freq = 0;

    for(;ip < program.size();) {
        std::stringstream ss{program[ip]};
        std::string c, p1, p2;
        ss >> c >> p1 >> p2;
        // std::cout << "\nip: " << ip << " : " << c << " : " << p1 << " : " << p2 << "\n";
        if (c == "snd") {
            freq = regOrVal(p1)->second;
        } else if (c == "set") {
            auto r1 = regOrVal(p1);
            r1->second = regOrVal(p2)->second;
        } else if (c == "add") {
            auto r1 = regOrVal(p1);
            r1->second += regOrVal(p2)->second;
        } else if (c == "mul") {
            auto r1 = regOrVal(p1);
            r1->second *= regOrVal(p2)->second;
        } else if (c == "mod") {
            auto r1 = regOrVal(p1);
            r1->second %= regOrVal(p2)->second;
        } else if (c == "rcv") {
            auto r1 = regOrVal(p1);
            if (r1->second) {
                r1->second = freq;
                std::cout << "freq: " << freq << "\n";
            }
        } else if (c == "jgz") {
            auto r1 = regOrVal(p1);
            if (r1->second > 0) {
                ip += regOrVal(p2)->second;
                continue;
            }
        } else {
            std::cerr << "ERROR: " << c << "\n";
        }
        ++ip;
    }

    return 0;
}
