#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

int cycle, val, sum = 0;
int x = 1;
string op;
int main() {
    for (int i=1; i<222; i++) {
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
        if ((i-20)%40 == 0) sum += i*x;
        cycle--;
    }
    cout << sum;
}
