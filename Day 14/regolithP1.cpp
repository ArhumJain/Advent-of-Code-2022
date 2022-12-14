#include "../utils/advent.h"

using namespace aoc;
using SegmentList = set<pair<pair<int,int>, pair<int,int>>>; 
constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

bool isOccupied(int x, int y, SegmentList &s) {
    for (auto &sg: s) {
        if (x == sg.first.first && x == sg.second.first) {
            if ((y >= sg.first.second && y <= sg.second.second) || (y <= sg.first.second && y >= sg.second.second)) return true;
        } else if (y == sg.first.second && y == sg.second.second) {
            if ((x >= sg.first.first && x <= sg.second.first) || (x <= sg.first.first && x >= sg.second.first)) return true;
        }
    }
    return false;
}
int main() {
    SegmentList segments;
    string read;
    vec<string> r;
    vec<string> start, end;
    int maxY = -1;
    int minX = 1000;
    int maxX = -1;
    while (true) {
        getline(f, read);
        r = split(read, " -> ");
        for (int i=0; i<r.size()-1; i++) {
            start = split(r[i], ",");
            end = split(r[i+1], ",");
            maxY = max(maxY, max(stoi(start[1]), stoi(end[1])));
            maxX = max(maxX, max(stoi(start[0]), stoi(end[0])));
            minX = min(minX, min(stoi(start[0]), stoi(end[0])));
            segments.insert(make_pair(make_pair(stoi(start[0]), stoi(start[1])), make_pair(stoi(end[0]), stoi(end[1]))));
        }
        if (f.eof()) break;
    }
    int currX = 500; int currY = 0;
    int settled = 0;
    pair<int, int> point;
    while (true) {
        if (isOccupied(currX, currY+1, segments)) {
            if (isOccupied(currX-1, currY+1, segments)) {
                if (isOccupied(currX+1, currY+1, segments)) {
                    settled++;
                    point = make_pair(currX, currY);
                    segments.insert(make_pair(point, point));
                    currX = 500;
                    currY = 0;
                } else {
                    currX++;
                    currY++;
                }

            } else {
                currX--;
                currY++;
            }
        } else currY++;
        if (currY > maxY) break;
    }
    cout << settled << endl;
}
