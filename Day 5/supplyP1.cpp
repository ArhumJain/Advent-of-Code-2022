#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#define TEST 0

using namespace std;

ifstream f(TEST == 1 ? "test.in" : "main.in");

string line = "";
vector<vector<char>> read;
vector<vector<char>> stacks;
int main() {
    int row = -1;
    std::getline(f,line);
    while (line[1] != '1') {
        row++;
        read.push_back(vector<char>());
        for (int i=1; i<line.size(); i+=4) read[row].push_back(line[i]);
        std::getline(f, line);
    }
    stacks = vector<vector<char>>(read[0].size(), vector<char>());
    for (int r = read.size()-1; r>-1; r--) {
        for (int c = 0; c<read[r].size(); c++) {
            if (read[r][c] == ' ') continue;
            stacks[c].push_back(read[r][c]);
        }
    }

    getline(f, line);
    int count, start, end; string _;
    while (true){
        f >> _ >> count >> _ >> start >> _ >> end;
        for (int i=0; i<count; i++) {
            stacks[end-1].push_back(stacks[start-1].back());
            stacks[start-1].pop_back();
        }
        if (f.eof()) break;
    }
    for (auto i: stacks) cout << i.back();
}