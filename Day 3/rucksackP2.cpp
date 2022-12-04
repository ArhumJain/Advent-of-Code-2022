
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
    int group = 1;
    while (true) {
        if (group == 4){
            group = 1;
            first.clear();
        } 
        f >> comp;
        if (group == 1) {
            for (int i = 0; i < comp.size(); i++) first[comp[i]] = 1;
            group++;
        }
        else {
            for (char i=0; i<comp.size(); i++) {
                if (first[comp[i]] == group-1) first[comp[i]]++;
                if (first[comp[i]] == 3) {
                    if (comp[i] > 96) sum += comp[i]-96;
                    else sum += comp[i]-38;
                    break;
                }
            }
            group++;
        }
        if (f.eof()) break;

    }
    cout << sum << endl;

}