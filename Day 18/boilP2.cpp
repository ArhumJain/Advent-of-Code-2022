#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

map<tuple<int,int,int>, bool> cuboids;
vec2d<int> dirs = {{1,0,0}, {-1,0,0}, {0,1,0}, {0,-1,0}, {0,0,1}, {0,0,-1}};
void fill() {
    int x, y, z;
    queue<tuple<int,int,int>> s;
    s.push({0,0,0});
    tuple<int,int,int> curr = s.front();
    while (!s.empty()) {
        tie(x,y,z) = curr;
        for (auto &dir: dirs) {
            cuboids[curr] = true;
            if (x < 0 || x > 30 || y < 0 || y > 30 || z < 0 || z > 30) break;
            if (cuboids[{x+dir[0],y+dir[1],z+dir[2]}] == false) {
                cuboids[{x+dir[0], y+dir[1], z+dir[2]}] = true;
                s.push({x+dir[0], y+dir[1], z+dir[2]});
            }
        }
        curr = s.front();
        s.pop();
    }
}

int main() {
    int count = 0; 
    int x, y, z;
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
    
    fill();
    int internalCount = 0;
    for (int xi=0; xi<30; xi++) {
        for (int yi=0; yi<30; yi++) {
            for (int zi=0; zi<30; zi++) {
                if (cuboids[{xi,yi,zi}] == false) {
                    for (auto &dir: dirs) {
                        if (cuboids[{xi+dir[0], yi+dir[1], zi+dir[2]}]) {
                            internalCount++;
                        }
                    }
                }
            }
        }
    }
    std::cout << count << endl;

    cout << count - internalCount << endl;
}
