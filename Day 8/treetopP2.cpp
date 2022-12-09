#include "../utils/advent.h"
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
    
    int max = -1;
    int score;
    int count;
    for (int r=0; r<grid.size(); r++) {
        for (int c=0; c<grid[r].size(); c++) {
            count = 0;
            score = 1;
            for (int ri = r-1; ri > -1; ri--) {
                count++;
                if (grid[ri][c].first >= grid[r][c].first) break;
            }
            score *= count;
            count = 0;
            for (int ri = r+1; ri<grid.size(); ri++) {
                count++;
                if (grid[ri][c].first >= grid[r][c].first) break;
            }
            score *= count;
            count = 0;
            for (int ci = c - 1; ci > -1; ci--) {
                count++;
                if (grid[r][ci].first >= grid[r][c].first) break;
            }
            score *= count;
            count = 0;
            for (int ci = c + 1; ci < grid[r].size(); ci++) {
                count++;
                if (grid[r][ci].first >= grid[r][c].first) break;
            }
            score *= count;
            if (score > max) max = score;
        }
    }
    cout << max << endl;
}
