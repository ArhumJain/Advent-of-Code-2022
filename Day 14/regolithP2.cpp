#include "../utils/advent.h"

using namespace aoc;
using SegmentList = set<pair<pair<int,int>, pair<int,int>>>; 
constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

bool isOccupied(int x, int y, map<pair<int,int>, bool> m) {
    return (m[make_pair(x, y)]);
    // for (auto &sg: m) {
    //     if (x == sg.first.first && x == sg.second.first) {
    //         if ((y >= sg.first.second && y <= sg.second.second) || (y <= sg.first.second && y >= sg.second.second)) {
    //             return true;
    //         }
    //     } else if (y == sg.first.second && y == sg.second.second) {
    //         if ((x >= sg.first.first && x <= sg.second.first) || (x <= sg.first.first && x >= sg.second.first)) {
    //             return true;
    //         }
    //     }
    // }
    return false;
}
int main() {
    SegmentList segments;
    map<pair<int,int>, bool> points;
    string read;
    vec<string> r;
    vec<string> start, end;
    int maxY = -1;
    while (true) {
        getline(f, read);
        r = split(read, " -> ");
        for (int i=0; i<r.size()-1; i++) {
            start = split(r[i], ",");
            end = split(r[i+1], ",");
            for (int x = min(stoi(start[0]), stoi(end[0])); x < max(stoi(start[0]), stoi(end[0]))+1; x++) {
                for (int y = min(stoi(start[1]), stoi(end[1])); y < max(stoi(start[1]), stoi(end[1]))+1; y++) {
                    points[make_pair(x, y)] = true;
                }
            }
            maxY = max(maxY, max(stoi(start[1]), stoi(end[1])));
            segments.insert(make_pair(make_pair(stoi(start[0]), stoi(start[1])), make_pair(stoi(end[0]), stoi(end[1]))));
        }
        if (f.eof()) break;
    }
    for (int x = 470; x < 540; x++) {
        points[make_pair(x, maxY+2)] = true;
    }
    // segments.insert(make_pair(make_pair(0,maxY+2), make_pair(1000, maxY+2)));
    int currX = 500; int currY = 0;
    int settled = 0;
    pair<int, int> point;
    while (true) {
        if (isOccupied(currX, currY+1, points)) {
            if (isOccupied(currX-1, currY+1, points)) {
                if (isOccupied(currX+1, currY+1, points)) {
                    settled++;
                    point = make_pair(currX, currY);
                    points[point] = true;
                    if (currX == 500 && currY == 0) break;
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
    }
    cout << settled << endl;
}
