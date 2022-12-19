#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

map<int, int> sizes = {{0,1}, {1, 3}, {2, 3}, {3, 4}, {4, 2}};
inline int shift(char op, int x) {
    return op == '>' ? x>>1 : x<<1;
    // if (op == '>') return (x>>1);
    // else return (x<<1);
}
inline bool checkEdges(char op, int x) {
    return (op == '>' ? !(x & 0b0000001) : !(x & 0b1000000));
}
// inline void setCurrBlock(int cycle, vec<int> &currBlock, vec2d<int> &blocks) {
//     currBlock.clear();
//     for (int i=0; i<blocks[cycle].size(); i++) {
//         currBlock.push_back(blocks[cycle][i]);
//     }
// }
int main() {
    // vec<bitset<7>> tower;
    vec<int> tower;
    vec<int> currBlock;
    vec2d<int> blocks = {{30}, {4, 14, 4}, {4, 4, 28}, {16, 16, 16, 16}, {24,24}};
    int maxHeight = 0;
    int cycle = 0;
    bool falling = false;
    int y;
    char op;
    while (true) {
        f >> op;
        if (!falling) {
            y = maxHeight + 3;
            currBlock = blocks[cycle];
            // for (auto i: currBlock) tower.push_back(0);
            for (int i=maxHeight; i<maxHeight+3; i++) tower.push_back(0);
            falling = true;
            cout << "Starting Block: " << endl;
            for (auto i: currBlock) {
                cout << bitset<7>(i) << endl;
            }
        }
        int idx = -1;
        if(none_of(currBlock.begin(), currBlock.end(), [&] (int &i) {
            idx++;
            return !(checkEdges(op, i) && ((tower[y+idx] & shift(op, i)) == 0));
        })) {
            cout << "--------------" << endl;
            for (int i=0; i<currBlock.size(); i++) {
                currBlock[i] = shift(op, currBlock[i]);
                cout << op << ": " << bitset<7>(currBlock[i]) << endl;
            }
            cout << "--------------" << endl;
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
            cycle++;
            falling = false;
            cout << "--------------" << endl;
            for (int i=tower.size()-1; i>-1; i--) {
                cout << bitset<7>(tower[i]) << endl;
            }
            cout << "--------------" << endl;
        }
        if (f.eof()) break;
    }
}

