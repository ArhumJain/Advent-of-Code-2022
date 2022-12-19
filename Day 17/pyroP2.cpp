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
    int repeats = 0;
    int previousMax = 0;
    int previousBlockCount =  0;

    ull baseHeight = 1000000000000-1748;
    while (blockCount != 1000000000000) {
        f >> op;
        if (!falling) {
            y = maxHeight + 4;
            currBlock = blocks[cycle];
            for (int i=maxHeight; i<maxHeight+4; i++) tower.push_back(0);
            falling = true;
            // cout << "Starting Block: " << endl;
            // for (auto i: currBlock) {
            //     cout << bitset<7>(i) << endl;
            // }
        }
        int idx = -1;
        if(none_of(currBlock.begin(), currBlock.end(), [&] (int &i) {
            idx++;
            return !(checkEdges(op, i) && ((tower[y+idx] & shift(op, i)) == 0));
        })) {
            // cout << "--------------" << endl;
            for (int i=0; i<currBlock.size(); i++) {
                currBlock[i] = shift(op, currBlock[i]);
                // cout << op << ": " << bitset<7>(currBlock[i]) << endl;
            }
            // cout << "--------------" << endl;
        }
        idx = -1;
        if (none_of(currBlock.begin(), currBlock.end(), [&] (int &i) {
            idx++;
            return y == 0 || (tower[y+idx-1] & i) != 0;
        })) {
            y--;
        } else {
            // cout << currBlock.size() << endl;
            for (int i=0; i<currBlock.size(); i++) {
                tower[y+i] |= currBlock[i];
            }
            maxHeight = max((int)(y+currBlock.size()-1), maxHeight);
            blockCount++;
            cycle = (cycle+1)%5;
            falling = false;
            // cout << "--------------" << endl;
            // for (int i=tower.size()-1; i>-1; i--) {
            //     cout << bitset<7>(tower[i]) << endl;
            // }
            // cout << "--------------" << endl;
        }
        if (f.eof()) {
            cout << "----------------------" << endl;
            for (int i=0; i<maxHeight; i++) {
                cout << bitset<7>(tower[i]) << endl;
            }
            cout << "----------------------" << endl;
            repeats++;
            if (blockCount > 10000000000) cout << "hi" << endl;
            cout << maxHeight+1 << " " << (maxHeight+1) - previousMax << " " << blockCount << " " << blockCount - previousBlockCount << endl;
            previousMax = maxHeight;
            previousBlockCount = blockCount;
            // cout << maxHeight << " " << blockCount <<  endl;
            // cout << maxHeight << endl;
            // if (repeats == 1000000) break;
            // cout << f.tellg() << endl;
            f.clear();
            // cout << f.tellg() << endl;
            f.seekg(1);
        }
    }
    cout << "Final max h: " << maxHeight+1 << endl;
}

