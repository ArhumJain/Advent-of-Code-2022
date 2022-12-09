#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");


map<pair<int, int>, bool> grid;
umap<char, pair<int, int>> dirMap = {{'U', {0, 1}}, {'D', {0, -1}}, {'L', {-1, 0}}, {'R', {1, 0}}};

int c = 0;
char dir;
int step;
pair<int, int> hPos = {0, 0};
pair<int, int> tPos = {0, 0};

int main() {
    while (true) {
        f >> dir >> step;
        if (f.eof()) break;
        for (int i=0; i<step; i++) {
            hPos.first += dirMap[dir].first;
            hPos.second += dirMap[dir].second;
            if (abs(hPos.first-tPos.first) + abs(hPos.second-tPos.second) > 1) {
                tPos.first = hPos.first - dirMap[dir].first;
                tPos.second -= hPos.second - dirMap[dir].second;
                if (grid[make_pair(tPos.first, tPos.second)] == false) {
                    grid[make_pair(tPos.first, tPos.second)] = true;
                    c++;
                }
            }
        }
    }
    cout << c;
}
