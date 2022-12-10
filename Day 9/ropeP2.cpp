#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

map<pair<int, int>, bool> grid;
umap<char, pair<int, int>> dirMap = {{'U', {0, 1}}, {'D', {0, -1}}, {'L', {-1, 0}}, {'R', {1, 0}}};
char dir; int step;
pair<int,int> knots[10] = {pair<int,int>(0,0)};
int main() {
    while (true) {
        f >> dir >> step;
        for (int i=0; i<step; i++) {
            knots[0].first += dirMap[dir].first; 
            knots[0].second += dirMap[dir].second;
            for (int k=1; k<10; k++) { 
                if (max(abs(knots[k-1].first-knots[k].first), abs(knots[k-1].second-knots[k].second)) > 1) {
                    if (knots[k].first != knots[k-1].first) knots[k].first += (knots[k-1].first-knots[k].first > 0 ? 1 : -1);
                    if (knots[k].second != knots[k-1].second) knots[k].second += (knots[k-1].second-knots[k].second > 0 ? 1 : -1);
                }
            }
            grid[{knots[9].first, knots[9].second}] = true;
        }
        if (f.eof()) break;
    }
    cout << grid.size();
}
