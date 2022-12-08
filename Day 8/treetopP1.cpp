#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

vec2d<tup<int, bool>> grid;
int main() {
    string row;
    int r = 0;
    while(true) {
        f>>row;
        grid.push_back(vec<tup<int, bool>>());
        for (int i=0; i<row.size(); i++) {
            grid[r][i] = tup<int, bool>((int) i, false);
        }
        if (f.eof()) break;
    }
}
