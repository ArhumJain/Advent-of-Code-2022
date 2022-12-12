#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

struct Node
{
    int r, c;
    int height;
    bool isEnd = false;
    bool visited = false;
    int level = 0;
    Node(int r, int c, char height)
    {
        this->r = r;
        this->c = c;
        this->height = height;
    }
};
bool isValid(vec2d<Node> &grid, Node &n, int r, int c)
{
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size())
        return false;
    else if (grid[r][c].height - n.height > 1)
        return false;
    else if (grid[r][c].visited)
        return false;
    return true;
}
int main()
{
    vec2d<Node> grid;
    vec<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    string r;
    int row = 0;
    Node *curr;
    queue<Node*> q;
    while (true)
    {
        f >> r;
        grid.push_back(vec<Node>());
        for (int i = 0; i < r.size(); i++)
        {
            grid[row].push_back(Node(row, i, r[i]));
            if (r[i] == 'S')
            {
                grid[row][i].level++;
                grid[row][i].height = 'a';
                curr = &grid[row][i];
            }
            else if (r[i] == 'E')
                grid[row][i].isEnd = true;
                grid[row][i].height = 'z';
        }
        row++;
        if (f.eof())
            break;
    }
    while (curr->isEnd != true)
    {
        for (auto &dir : dirs)
        {
            if (isValid(grid, *(curr), curr->r + dir.first, curr->c + dir.second))
            {
                q.push(&grid[curr->r + dir.first][curr->c + dir.second]);
            }
        }
        q.front()->level = curr->level + 1;
        curr = q.front();
        q.pop();
    }
    cout << curr->level << endl;
    cout << curr->r << " " << curr->c << endl;
}