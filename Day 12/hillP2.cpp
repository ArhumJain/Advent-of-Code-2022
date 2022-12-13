#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

struct Node {
    int r, c, height;
    bool isEnd = false;
    bool visited = false;
    int level = 0;
    Node *parent;
    Node(int r, int c, char height) {
        this->r = r;
        this->c = c;
        this->height = height;
    }
};
bool isValid(vec2d<Node> &grid, Node &n, int r, int c) {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return false;
    else if (grid[r][c].height - n.height > 1) return false;
    else if (grid[r][c].visited) return false;
    return true;
}
void clear(vec2d<Node> &grid) {
    for (auto &row: grid) {
        for (auto &n: row) {
            n.visited = false;
            n.level = 0;
        }
    }
}
int main() {
    vec<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vec2d<Node> grid;
    Node *curr;
    queue<Node*> q;
    int row = 0;
    int y, x;
    string r;
    while (true) {
        f >> r;
        grid.push_back(vec<Node>());
        for (int i = 0; i < r.size(); i++) {
            grid[row].push_back(Node(row, i, r[i]));
            if (r[i] == 'S') {
                grid[row][i].height = 'a';
            }
            else if (r[i] == 'E') {
                grid[row][i].isEnd = true;
                grid[row][i].height = 'z';
            }
        }
        row++;
        if (f.eof()) break;
    }
    curr = &grid[y][x];
    Node *neighbor;
    int minimum = 1000;
    for (auto &row: grid) {
        for (auto &n: row) {
            if (n.height == 97) {
                curr = &n;
                clear(grid);
                q = queue<Node*>();
                curr->visited = true;
                while (curr != nullptr && !curr->isEnd) {
                    for (auto &dir : dirs) {
                        if (isValid(grid, *(curr), curr->r + dir.first, curr->c + dir.second)) {
                            neighbor = &grid[curr->r + dir.first][curr->c + dir.second];
                            neighbor->level = curr->level+1;
                            neighbor->visited = true;
                            q.push(neighbor);
                        }
                    }
                    if (q.size() == 0) {
                        goto label; // quick hack, i am tired, i love cpp because you can can abuse power like this
                        // whoever said with great power comes great responsibility? exactly, no one
                        // imagine talking to yourself in a text file among millions of text files on a website
                        // that's really just a text file embedded in pieces of metal in some dark server room.
                    }
                    curr = q.front();
                    q.pop();
                }
                minimum = min(minimum, curr->level);
                label: continue;
            }
        }
    }
    cout << minimum;
}