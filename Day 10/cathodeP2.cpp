#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

int cycle, val, sum = 0;
int x = 1;
string op;
vec2d<char> crt(6, vec<char>(40, '.'));
int main() {
    for (auto &row: crt) {
        for (int i=0; i<40; i++) {
            if (cycle == 0) {
                f >> op; x += val;
                if (op == "addx") {
                    f >> val;
                    cycle = 2;
                } else {
                    cycle = 1;
                    val = 0;
                }
            }
            if (i==x || i == x-1 || i == x+1) row[i] = '#';
            cycle--;

        }
    }
    print2d(crt);
}
