#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

map<tuple<int,int,int>, bool> cuboids;
vec2d<int> dirs = {{1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}};
int main() {
    int count = 0; 
    int x, y, z
    char _;
    while (true) {
        f >> x >> y >> z;
        cuboids[{x,y,z}] = true;
        if (f.eof()) break;
    }
    for (auto &c: cuboids) {
        tie(x,y,z) = c.first;
        for (auto &dir: dirs) {
            try { cuboids.at({x+dir[0], y+dir[1], z+dir[2]}); }
            catch (...) { count++; }
        }
    }
    std::cout << count << endl;
}
