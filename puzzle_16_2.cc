// Copyright (C) 2017, Seznam.cz, a.s.

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

struct Op {
    enum { SPIN, SWAP_PROG, SWAP_POS } op;
    union POS {
        unsigned char c;
        int pos;
    };
    POS a, b;
};

std::vector<Op> ops;

void spin(std::string& data, const Op& op)
{
    int dist = data.size() - op.a.pos;
    for (int j = dist; j < data.size(); ++j) {
        int pos = j;
        for (int i = 0; i < dist; ++i, --pos) {
            std::swap(data[pos-1], data[pos]);
        }
    }
}

void swap_prog(std::string& data, const Op& op)
{
    std::swap(data[op.a.pos], data[op.b.pos]);
}

void swap_pos(std::string& data, const Op& op)
{
    std::swap(data[data.find(op.a.c)], data[data.find(op.b.c)]);
}

int main()
{
    std::string data{"abcdefghijklmnop"};

    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> words;
    boost::algorithm::split(
        words, line, boost::is_any_of(","), boost::algorithm::token_compress_on);
    for (const auto& cmd : words) {
        if (cmd[0] == 's') {
            Op op;
            op.op = Op::SPIN;
            op.a.pos = atoi(&cmd[1]);
            ops.push_back(op);
        } else if (cmd[0] == 'x') {
            Op op;
            op.op = Op::SWAP_PROG;
            op.a.pos = atoi(&cmd[1]);
            op.b.pos = atoi(&cmd[cmd.find('/')+1]);
            ops.push_back(op);
        } else if (cmd[0] == 'p') {
            Op op;
            op.op = Op::SWAP_POS;
            op.a.c = cmd[1];
            op.b.c = cmd[3];
            ops.push_back(op);
        } else {
            std::cerr << "ERROR: " << cmd << "\n";
            return 1;
        }
    }

    std::cout << "Ops: " << ops.size() << "\n";

    std::unordered_set<std::string> results;
    std::string lastR;

    for (int i = 0; i < 1000000000; ++i) {
        for (const auto& op : ops) {
            if (op.op == Op::SPIN) {
                spin(data, op);
            } else if (op.op == Op::SWAP_PROG) {
                swap_prog(data, op);
            } else if (op.op == Op::SWAP_POS) {
                swap_pos(data, op);
            }
        }
        if (!results.insert(data).second) {
            std::cout << "Found loop at " << i << ", current result " << data
                      << ", last result: " << lastR << "\n";
        }
        if (i % 10000 == 0) {
            std::cout << i / 10000000. << "%\n";
        }
        lastR = data;
    }
    std::cout << "data: " << data << "\n";
    return 0;
}
