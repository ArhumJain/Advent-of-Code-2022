#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

pair<int,int> getColumnBound(int col, vec<string> &map) {
    int lower = 0;
    int upper = map.size()-1;
    for (int row=0; row<map.size()-2; row++) {
        if (col < map[row].size() && map[row][col] != ' ') { lower = row; break; }
    }
    for (int row=map.size()-3; row>-1; row--) {
        if (col < map[row].size() && map[row][col] != ' ') { upper = row; break; }
    }
    return {lower, upper};
}

pair<int,int> getRowBound(int row, vec<string> &map) {
    int lower = 0;
    int upper = map[row].size()-1;
    for (int col=0; col<map[row].size(); col++) {
        if (map[row][col] != ' ') { lower = col; break; }
    }
    for (int col=map[row].size()-1; col>-1; col--) {
        if (map[row][col] != ' ') { upper = col; break; }
    }
    return {lower, upper};
}
int main() {
    vec<pair<int,int>> rowBounds;
    vec<pair<int,int>> colBounds;
    vec<pair<int,int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    vec<string> map = readlines(f);
    vec<string> path = split(map[map.size()-1]);
    int row = 0;
    int col = map[0].find('.');
    int facing = 0;
    for (int i=0; i<map.size()-2; i++) rowBounds.push_back(getRowBound(i, map));
    // for (int i=0; i<map[map.size()-3].size(); i++) { // For test input
    //     colBounds.push_back(getColumnBound(i, map));
    // }
    for (int i=0; i<map[0].size(); i++) colBounds.push_back(getColumnBound(i, map)); // For main input

    int nextRow, nextCol;
    for (int i=0; i<path.size(); i++) {
        if (path[i] == "R") facing = (facing+1)%4;
        else if (path[i] == "L") facing = (facing+3)%4;
        else {
            for (int step=1; step<=stoi(path[i]); step++) {
                nextRow = row+dirs[facing].second;
                nextCol = col+dirs[facing].first;
                if (nextCol < rowBounds[nextRow].first || nextCol > rowBounds[nextRow].second) {
                    if (facing == 0) nextCol = rowBounds[nextRow].first;
                    else if (facing == 2) nextCol = rowBounds[nextRow].second;
                }

                if (nextRow < colBounds[nextCol].first || nextRow > colBounds[nextCol].second) {
                    if (facing == 3) nextRow = colBounds[nextCol].second;
                    else if (facing == 1) nextRow = colBounds[nextCol].first;
                }
                if (map[nextRow][nextCol] == '#') break;
                else {
                    row = nextRow;
                    col = nextCol;
                }
            }
        }
    }
    cout << 1000 * (row+1) + 4 * (col+1) + facing << endl;
}
