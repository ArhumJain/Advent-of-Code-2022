#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
constexpr ll BLOCKS = 1000000000000;
F f(TEST == 1 ? "test.in" : "main.in");

map<int, int> sizes = {{0,1}, {1, 3}, {2, 3}, {3, 4}, {4, 2}};
map<tuple<int, int, int,int,int>, pair<int, int>> state;
inline int shift(char op, int x) { return op == '>' ? x>>1 : x<<1; }
inline bool checkEdges(char op, int x) { return (op == '>' ? !(x&1):!(x&64)); }
int main() {
    vec<int> tower, currBlock;
    vec2d<int> blocks = {{30}, {8, 28, 8}, {28, 4, 4}, {16, 16, 16, 16}, {24,24}};
    ll maxHeight = -1;
    int cycle = 0;
    bool falling = false;
    int y;
    ll blockCount = 0;
    char op;
    bool jump = false;
    int blockInterval;
    int heightDiff;
    int blockBound = -1;
    ll blocksRemaining;
    ll jumpHeight;
    ll baseHeight;
    while (true) {
        if (jump && blockCount == blockBound) {
            break;
        }
        f >> op;
        if (!falling) {
            y = maxHeight + 4;
            currBlock = blocks[cycle];
            for (ll i=maxHeight; i<maxHeight+4; i++) tower.push_back(0);
            falling = true;
        }
        int idx = -1;
        if(none_of(currBlock.begin(), currBlock.end(), [&] (int &i) {
            idx++;
            return !(checkEdges(op, i) && ((tower[y+idx] & shift(op, i)) == 0));
        })) {
            for (int i=0; i<currBlock.size(); i++) {
                currBlock[i] = shift(op, currBlock[i]);
            }
        }
        idx = -1;
        if (none_of(currBlock.begin(), currBlock.end(), [&] (int &i) {
            idx++;
            return y == 0 || (tower[y+idx-1] & i) != 0;
        })) {
            y--;
        } else {
            maxHeight = max((ll)(y+currBlock.size()-1), maxHeight);
            blockCount++;
            for (int i=0; i<currBlock.size(); i++) tower[y+i] |= currBlock[i];
            if (state[{tower[y], tower[y+1], tower[y+2], f.tellg(), cycle}].second == 0) {
                cout << (int) f.tellg() << " " << cycle << endl;
                state[{tower[y], tower[y+1], tower[y+2], f.tellg(), cycle}] = {maxHeight+1, blockCount};
            } else if (!jump) {
                cout << f.tellg() << " " << cycle << endl;
                heightDiff = (maxHeight+1) - state[{tower[y], tower[y+1], tower[y+2], f.tellg(), cycle}].first+3;
                blockInterval = blockCount - state[{tower[y], tower[y+1], tower[y+2], f.tellg(), cycle}].second;
                blocksRemaining = BLOCKS - blockCount;
                blockBound = (blocksRemaining)%blockInterval;
                jumpHeight = (maxHeight + 1) + ((blocksRemaining-(blocksRemaining%blockInterval))/blockInterval)*heightDiff;
                baseHeight = maxHeight;
                blockCount = 0;
                jump = true;
            }
            cycle = (cycle+1)%5;
            falling = false;
        }
        if (f.eof()) {
            f.clear();
            f.seekg(1);
        }
    }
    cout << ((maxHeight+1)-(baseHeight+1)) + jumpHeight << endl;
}

