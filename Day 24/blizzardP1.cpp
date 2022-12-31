#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

int END_ROW;
int END_COL;
map<pair<int,int>, vec<char>> simulateBlizzards(map<pair<int,int>, vec<char>> blizzardPositions) {
    char b;
    map<pair<int,int>, vec<char>> next;
    for (auto &m: blizzardPositions) {
        for (char &c: m.second) {
            if (c == '<') {
                if (m.first.second-1 == 0) next[{m.first.first,END_COL-1}].push_back(c);
                else next[{m.first.first, m.first.second-1}].push_back(c);
            } else if (c == '>') {
                if (m.first.second+1 == END_COL) next[{m.first.first, 1}].push_back(c);
                else next[{m.first.first, m.first.second+1}].push_back(c);
            } else if (c == '^') {
                if (m.first.first-1 == 0) next[{END_ROW-1, m.first.second}].push_back(c);
                else next[{m.first.first-1, m.first.second}].push_back(c);
            } else if (c == 'v') {
                if (m.first.first+1 == END_ROW) next[{1, m.first.second}].push_back(c);
                else next[{m.first.first+1, m.first.second}].push_back(c);
            }
        }
    }
    return next;
}
bool compareBlizzardStates(map<pair<int,int>, vec<char>> &a, map<pair<int,int>, vec<char>> &b) {
    for (auto &m: a) {
        sort(m.second.begin(), m.second.end());
        sort(b[m.first].begin(), b[m.first].end());
        if (!(m.second == b[m.first])) return false;
    }
    return true;
}

struct Node {
    int row, col, minute;
    Node() {}
    Node (int r, int c, int m) { row = r; col = c; minute = m; }
};
vec<pair<int,int>> dirs = {{0,0}, {1,0}, {0,1}, {-1,0}, {0,-1}};
int main() {
    string r;    
    int row = -1;
    map<pair<int,int>, vec<char>> firstBlizzardState;
    while (true) {
        f >> r;
        row++;
        for (int i=0; i<r.size(); i++) {
            if (r[i] != '#' && r[i] != '.') firstBlizzardState[{row, i}].push_back(r[i]);
        }
        if (f.eof()) break;
    }
    END_ROW = row;
    END_COL = r.size()-1;

    map<pair<int,int>, vec<char>> currBlizardState = firstBlizzardState;

    vec<map<pair<int,int>, bool>> availablePositions;
    do {
        availablePositions.push_back(map<pair<int,int>, bool>());
        availablePositions[availablePositions.size()-1][{0,1}] = true;
        availablePositions[availablePositions.size()-1][{END_ROW,END_COL-1}] = true;
        for (int r=1; r<END_ROW; r++) {
            for (int c=1; c<END_COL; c++) {
                if (currBlizardState[{r, c}].size() == 0) availablePositions[availablePositions.size()-1][{r,c}] = true;
            }
        }
        currBlizardState = simulateBlizzards(currBlizardState);
    } while (!compareBlizzardStates(firstBlizzardState, currBlizardState));
    int cycleSize = availablePositions.size();
    Node curr;
    queue<Node> q;
    q.push(Node(0,1,1));
    bool moved = false;
    int targetRow = row;
    int targetCol = r.size()-2;
    map<tuple<int,int,int>, bool> cache;
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        if (curr.row == targetRow && curr.col == targetCol) {
            cout << curr.minute-1 << endl;
            return 1;
        }
        moved = false;
        for (auto &dir: dirs) {
            if (availablePositions[curr.minute%cycleSize][{curr.row+dir.first, curr.col+dir.second}]) {
                if (cache[{curr.row+dir.first, curr.col+dir.second, (curr.minute+1)%cycleSize}]) continue;
                else cache[{curr.row+dir.first, curr.col+dir.second, (curr.minute+1)%cycleSize}] = true;
                q.push(Node(curr.row+dir.first, curr.col+dir.second, curr.minute+1));
                moved = true;
            }
        }
    }
}