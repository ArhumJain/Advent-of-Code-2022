#include "../utils/advent.h"

using namespace aoc; // I dislike cubes. Didn't like them last year, don't like them this year :(.

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

enum Facing { RIGHT, DOWN, LEFT, UP };

tuple<int,int,int> getNextPosFace(int row, int col, int facing, vec<pair<int,int>> &dirs)
{
    int nextRow = row+dirs[facing].second;
    int nextCol = col+dirs[facing].first;
    int nextFacing = facing;
    switch (facing) {
        case Facing::UP:
            if (row == 0 && col < 100) return {150 + (col%50), 0, Facing::RIGHT};
            else if (row == 0 && col >= 100) return {199, col%50, Facing::UP};
            else if (row == 100 && col < 50) return {50 + (col%50), 50, Facing::RIGHT};
            break;
        case Facing::DOWN:
            if (row == 199) return {0, 100+(col%50), Facing::DOWN};
            else if (row == 149 && col >= 50) return {150+(col%50), 49, Facing::LEFT};
            else if (row == 49 && col >= 100) return {50 + (col%50), 99, Facing::LEFT};
            break;
        case Facing::LEFT:
            if (col == 50 && row < 50) return {149 - (row%50), 0, Facing::RIGHT};
            else if (col == 50 && (row >= 50 && row < 100)) return {100, row%50, Facing::DOWN};
            else if (col == 0 && row >= 150) return {0, 50+(row%50), Facing::DOWN};
            else if (col == 0 && row >= 100) return {49 - (row%50), 50, Facing::RIGHT};
            break;
        case Facing::RIGHT:
            if (col == 149) { return {149-(row%50), 99, Facing::LEFT};}
            else if (col == 99 && row>=100) return {49-(row%50), 149, Facing::LEFT};
            else if (col == 99 && row >= 50) return {49, 100+(row%50), Facing::UP};
            else if (col == 49 && row >= 150) return {149, 50+(row%50), Facing::UP}; 
            break;
    }
    return {nextRow, nextCol, nextFacing};
}
int main() {
    vec<pair<int,int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1}};
    vec<string> map = readlines(f);
    vec<string> path = split(map[map.size()-1]);
    int row = 0;
    int col = map[0].find('.');
    int facing = 0;
    int nextRow, nextCol, nextFacing;
    for (int i=0; i<path.size(); i++) {
        if (path[i] == "R") facing = (facing+1)%4;
        else if (path[i] == "L") facing = (facing+3)%4;
        else {
            for (int step=1; step<=stoi(path[i]); step++) {
                tie(nextRow, nextCol, nextFacing) = getNextPosFace(row, col, facing, dirs);
                if (map[nextRow][nextCol] == '#') break;
                else {
                    row = nextRow;
                    col = nextCol;
                    facing = nextFacing;
                }
            }
        }
    }
    cout << 1000 * (row+1) + 4 * (col+1) + facing << endl;
}