#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
constexpr int MAXY = 165;
F f(TEST == 1 ? "test.in" : "main.in");
struct Point {
    bool isSettled = false;
    bool isSand = false;
};
bool isOccupied(int x, int y, vec2d<Point> &grid) {return (grid[y][x].isSettled || x < 0 || x >= grid[0].size());}
int main() {
    vec2d<Point> grid(MAXY+3, vec<Point>(700));
    const vec<pair<int,int>> dirs = {{0, 1}, {-1,1}, {1,1}};
    vec<string> start, end;
    vec<string> r;
    string read;
    while (true) {
        getline(f, read);
        r = split(read, " -> ");
        for (int i=0; i<r.size()-1; i++) {
            start = split(r[i], ",");
            end = split(r[i+1], ",");
            for (int x = min(stoi(start[0]), stoi(end[0])); x < max(stoi(start[0]), stoi(end[0]))+1; x++) {
                for (int y = min(stoi(start[1]), stoi(end[1])); y < max(stoi(start[1]), stoi(end[1]))+1; y++) grid[y][x].isSettled = true;
            }
        }
        if (f.eof()) break;
    }
    int settled = 0;
    bool filled = false;
    for (int x=0; x<grid[0].size(); x++) grid[grid.size()-1][x].isSettled = true;
    while (!filled) {
        grid[0][500].isSand = true;
        for (int y=grid.size()-2; y>-1; y--) {
            for (int x=0; x<grid[0].size(); x++) {
                if (grid[y][x].isSand && !grid[y][x].isSettled) {
                    for (auto &dir: dirs) {
                        if (!isOccupied(x+dir.first, y+dir.second, grid)) {
                            grid[y+dir.second][x+dir.first].isSand = true;
                            grid[y][x].isSand = false;
                            break;
                        }
                    }
                    if (grid[y][x].isSand) {
                        settled++;
                        grid[y][x].isSettled = true;
                        if (y == 0 && x == 500) {
                            filled = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    cout << settled << endl;
    return 0;
}