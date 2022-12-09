#include "../utils/advent.h"
// could probably put all the repetitive code but too lazy too :(
using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

vec2d<pair<int, bool>> grid;
int main() {
    string row;
    int r = 0;

    while(true) {
        f>>row;
        grid.push_back(vec<pair<int, bool>>());
        for (int i=0; i<row.size(); i++) {
            grid[r].push_back(make_pair(row[i]-'0', false));
        }
        r++;
        if (f.eof()) break;
    }
    int count = (grid[0].size()*2) + (grid.size()*2) - 4;
    int max;

    for (int r=1; r<grid.size()-1; r++) {
        max = grid[r][0].first;
        for (int c=1; c<grid[r].size()-1; c++) {
            if ((grid[r][c]).first > max) {
                max = grid[r][c].first;
                if (grid[r][c].second == false) {
                    grid[r][c].second = true;
                    count++;
                }
            }
        }
        max = grid[r][grid[0].size()-1].first;
        for (int c=grid[r].size()-2; c > 0; c--) {
            if ((grid[r][c]).first > max) {
                max = grid[r][c].first;
                if (grid[r][c].second == false) {
                    grid[r][c].second = true;
                    count++;
                }
            }
        }
    }

    for (int c=1; c<grid[0].size()-1; c++) {
        max = grid[0][c].first;
        for (int r=1; r<grid.size()-1; r++) {
            if ((grid[r][c]).first > max) {
                max = grid[r][c].first;
                if (grid[r][c].second == false) {
                    grid[r][c].second = true;
                    count++;
                }
            }
        }
        max = grid[grid.size()-1][c].first;
        for (int r = grid.size()-2; r > 0; r--) {
            if ((grid[r][c]).first > max) {
                max = grid[r][c].first;
                if (grid[r][c].second == false) {
                    grid[r][c].second = true;
                    count++;
                }
            }
        }
    }

    cout << count;
}
