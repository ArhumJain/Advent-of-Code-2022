#include <iostream>
#include <algorithm>
#include <fstream>

#define TEST 0

using namespace std;

ifstream f(TEST == 1 ? "test.in" : "main.in");

int l1, r1;
int l2, r2;
char a;
int c = 0;
int main() {
    while (true) {
        f >> l1 >> a >> r1 >> a >> l2 >> a >> r2;
        if (l1 >= l2 && r1 <= r2) c++;
        else if (l2 >= l1 && r2 <= r1) c++;
        if (f.eof()) break;
    }
    cout << c << endl;
}