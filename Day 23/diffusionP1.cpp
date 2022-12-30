#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

enum Directions { NORTH, SOUTH, WEST, EAST };
struct Elf {
    static const map<int, vec<pair<int,int>>> dirs;
    pair<int,int> proposed;
    pair<int,int> curr;
    Elf(int row, int col) { curr = {row, col}; }
    void propose(vec<Elf> &elves, map<pair<int,int>, bool> &grid, map<pair<int,int>, vec<Elf*>> &propositions, deque<int> &dq) {
        for (int r=-1; r<=1; r++) {
            for (int c=-1; c<=1; c++) {
                if (grid[{curr.first+r,curr.second+c}] && !(r == 0 && c == 0)) {
                    vec<pair<int,int>> d;
                    for (int i=0; i<4; i++) {
                        d = dirs.at(dq[i]);
                        if (none_of(d.begin(), d.end(), [&](const pair<int,int> &p) {return grid[{curr.first+p.first, curr.second+p.second}];})) {
                            propositions[{curr.first+d[1].first, curr.second+d[1].second}].push_back(this);
                            proposed.first = curr.first+d[1].first;
                            proposed.second = curr.second+d[1].second;
                            return;
                        }
                    }
                    r=2; c=2;
                }
            }
        }
        proposed.first = curr.first;
        proposed.second = curr.second;
    }

};
const map<int, vec<pair<int,int>>> Elf::dirs = {
    {NORTH, {{-1,-1}, {-1,0}, {-1,1}}},
    {SOUTH, {{1,-1}, {1,0}, {1,1}}},
    {WEST, {{-1,-1}, {0,-1}, {1,-1}}},
    {EAST, {{-1,1}, {0,1}, {1,1}}}
};
int main() {
    map<pair<int,int>, bool> grid;
    deque<int> dq = {NORTH, SOUTH, WEST, EAST};
    string r;
    vec<Elf> elves;
    int row = 0; 
    while (true) {
        f >> r;
        for (int i=0; i<r.size(); i++) {
            if (r[i] == '#') {
                elves.push_back(Elf(row, i));
                grid[{row, i}] = true;
            }
        }
        row++;
        if (f.eof()) break;
    }

    map<pair<int,int>, vec<Elf*>> propositions;
    for (int i=0; i<10; i++) {
        propositions.clear();
        for (Elf &elf: elves) elf.propose(elves, grid, propositions, dq);
        for (auto &p: propositions) {
            if (p.second.size() == 1) {
                grid[{p.first.first, p.first.second}] = true;
                grid[{p.second[0]->curr.first, p.second[0]->curr.second}] = false;
                p.second[0]->curr.first = p.first.first;
                p.second[0]->curr.second = p.first.second;
            }
        }
        dq.push_back(dq.front());
        dq.pop_front();
    }
    int left = 999;
    int right = -999;
    int top = 999;
    int bot = -999;
    for (Elf &elf: elves) {
        left = min(left, elf.curr.second);
        right = max(right, elf.curr.second);
        top = min(top, elf.curr.first);
        bot = max(bot, elf.curr.first);
    }
    cout << ((right-left)+1) * ((bot-top)+1) - elves.size() << endl;
}
