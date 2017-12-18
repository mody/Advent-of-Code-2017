#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
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

using Program = std::vector<std::string>;
using Queue = std::deque<int>;

struct Registers {
    using Storage = std::map<std::string, long>;
    using iterator = Storage::iterator;

    Registers(int pid) : registers{{"p", pid}}
    {}

    iterator regOrVal(const std::string& input)
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

    private:
        Storage registers;
};

struct Context {
    Context(const Program& _program, int _pid, Queue& _rq, Queue& _wq)
        : program(_program)
        , registers{_pid}
        , rq(_rq)
        , wq(_wq)
        , pid(_pid)
    {}

    const Program& program;
    Registers registers;
    Queue& rq;
    Queue& wq;
    int pid;
    int ip = 0;
    int freq = 0;

    bool step() {
        if (ip >= program.size()) {
            return false;
        }

        std::stringstream ss{program[ip]};
        std::string c, p1, p2;
        ss >> c >> p1 >> p2;
        // std::cout << "\nip: " << ip << " : " << c << " : " << p1 << " : " << p2 << "\n";
        if (c == "snd") {
            wq.push_back(registers.regOrVal(p1)->second);
            std::cout << "pid: " << pid << " - send " << wq.back() << "\n";
        } else if (c == "set") {
            auto r1 = registers.regOrVal(p1);
            r1->second = registers.regOrVal(p2)->second;
        } else if (c == "add") {
            auto r1 = registers.regOrVal(p1);
            r1->second += registers.regOrVal(p2)->second;
        } else if (c == "mul") {
            auto r1 = registers.regOrVal(p1);
            r1->second *= registers.regOrVal(p2)->second;
        } else if (c == "mod") {
            auto r1 = registers.regOrVal(p1);
            r1->second %= registers.regOrVal(p2)->second;
        } else if (c == "rcv") {
            if (rq.empty()) {
                // block
                std::cout << "pid: " << pid << " - recv blocked\n";
                return true;
            }
            auto r1 = registers.regOrVal(p1);
            r1->second = rq.front();
            rq.pop_front();
            std::cout << "pid: " << pid << " - recv " << r1->second << "\n";
        } else if (c == "jgz") {
            auto r1 = registers.regOrVal(p1);
            if (r1->second > 0) {
                ip += registers.regOrVal(p2)->second;
                return true;
            }
        } else {
            std::cerr << "ERROR: " << c << "\n";
        }
        ++ip;
        return true;
    }
};




int main()
{
    Program program;

    std::string line;
    while (std::getline(std::cin, line)) {
        program.emplace_back(std::move(line));
    }

    Queue q0, q1;
    Context c0(program, 0, q0, q1);
    Context c1(program, 1, q1, q0);

    for (;;) {
        bool pid0 = c0.step();
        bool pid1 = c1.step();
        if (!pid0 && !pid1) {
            break;
        }
    }

    return 0;
}
