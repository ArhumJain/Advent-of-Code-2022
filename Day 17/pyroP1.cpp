#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 0 ? "test.in" : "main.in");

map<int, int> sizes = {{0,1}, {1, 3}, {2, 3}, {3, 4}, {4, 2}};
inline int shift(char op, int x) { return op == '>' ? x>>1 : x<<1; }
inline bool checkEdges(char op, int x) { return (op == '>' ? !(x&1):!(x&64)); }
int main() {
    vec<int> tower, currBlock;
    vec2d<int> blocks = {{30}, {8, 28, 8}, {28, 4, 4}, {16, 16, 16, 16}, {24,24}};
    int maxHeight = -1;
    int cycle = 0;
    bool falling = false;
    int y;
    int blockCount = 0;
    char op;
    while (blockCount != 2022) {
        f >> op;
        if (!falling) {
            y = maxHeight + 4;
            currBlock = blocks[cycle];
            for (int i=maxHeight; i<maxHeight+4; i++) tower.push_back(0);
            falling = true;
        }
        int idx = -1;
        if(none_of(currBlock.begin(), currBlock.end(), [&] (int &i) { idx++;
            return !(checkEdges(op, i) && ((tower[y+idx] & shift(op, i)) == 0));
        })) {
            for (int i=0; i<currBlock.size(); i++) currBlock[i] = shift(op, currBlock[i]);
        }
        idx = -1;
        if (none_of(currBlock.begin(), currBlock.end(), [&] (int &i) { idx++;
            return y == 0 || (tower[y+idx-1] & i) != 0;
        })) y--;
        else {
            for (int i=0; i<currBlock.size(); i++) tower[y+i] |= currBlock[i];
            maxHeight = max((int)(y+currBlock.size()-1), maxHeight);
            blockCount++;
            cycle = (cycle+1)%5;
            falling = false;
        }
        if (f.eof()) { f.clear(); f.seekg(1); }
    }
    cout << maxHeight+1 << endl;
}

