#include "../utils/advent.h"
// Thought some more after solving part 2 and this is what I came up with. ~48ms runtime.
using namespace aoc;

constexpr int TEST = 0;
constexpr int MAXY = 165;
F f(TEST == 1 ? "test.in" : "main.in");
void recurse(int x, int y, map<pair<int,int>, bool> &points, int &settled) {
    points[make_pair(x,y)] = true; settled++;
    if (points[make_pair(x,y+1)] == false) recurse(x, y+1, points, settled);
    if (points[make_pair(x-1,y+1)] == false) recurse(x-1, y+1, points, settled);
    if (points[make_pair(x+1,y+1)] == false) recurse(x+1, y+1, points, settled);
    return;
}
int main() {
    map<pair<int, int>, bool> points;
    vec<string> start, end, r;
    string read;
    while (true) {
        getline(f, read);
        r = split(read, " -> ");
        for (int i=0; i<r.size()-1; i++) {
            start = split(r[i], ","); end = split(r[i+1], ",");
            for (int x = min(stoi(start[0]), stoi(end[0])); x < max(stoi(start[0]), stoi(end[0]))+1; x++) {
                for (int y = min(stoi(start[1]), stoi(end[1])); y < max(stoi(start[1]), stoi(end[1]))+1; y++) points[make_pair(x, y)] = true;
            }
        }
        if (f.eof()) break;
    }
    int settled = 0;
    for (int x=0; x<700; x++) points[make_pair(x, MAXY+2)] = true;
    recurse(500, 0, points, settled);
    cout << settled << endl;
}