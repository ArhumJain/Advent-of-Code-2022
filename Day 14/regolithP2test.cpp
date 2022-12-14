#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");
struct Point {
    bool isRock = false;
    bool isSand = false;

    friend ostream& operator<<(ostream &os, const Point &p) {
        if (p.isRock) os << "#";
        else if (p.isSand) os << "o";
        else os << ".";
        // os << s;
        return os;
    }
};
int main() {
    vec2d<Point> grid(168, vec<Point>(57));
    vec<string> start, end;
    vec<string> r;
    string read;
    // int maxY = -1;
    while (true) {
        getline(f, read);
        r = split(read, " -> ");
        for (int i=0; i<r.size()-1; i++) {
            start = split(r[i], ",");
            end = split(r[i+1], ",");
            for (int x = min(stoi(start[0]), stoi(end[0])); x < max(stoi(start[0]), stoi(end[0]))+1; x++) {
                for (int y = min(stoi(start[1]), stoi(end[1])); y < max(stoi(start[1]), stoi(end[1]))+1; y++) {
                    grid[y][x-483].isRock = true;
                }
            }
            // maxY = max(maxY, max(stoi(start[1]), stoi(end[1])));
        }
        if (f.eof()) break;
    }
    for (int x=0; x<grid[0].size(); x++) grid[grid.size()-1][x].isRock = true;
    for (int y=grid.size()-2; y>-1; y--) {
        for (int x=0; x<grid[0].size(); x++) {

        }
    }
}