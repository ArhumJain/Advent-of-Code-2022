#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#define TEST 0

using namespace std;

ifstream f(TEST == 1 ? "test.in" : "main.in");

int main() {
    string comp;
    unordered_map<char, int> first;
    int sum = 0;
    while (true) {
        first.clear();
        f >> comp;
        for (int i = 0; i < comp.size()/2; i++) {
            first[comp[i]] = 1;
        }
        for (int i=comp.size()/2; i < comp.size(); i++) {
            cout << comp[i] << endl;
            if (first[comp[i]] == 1) {
                if (comp[i] > 96) sum += comp[i]-96;
                else sum += comp[i]-38;
                break;
            }
        }
        if (f.eof()) break;

    }
    cout << sum << endl;

}