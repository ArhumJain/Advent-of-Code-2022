#include <iostream>
#include <fstream>


#define TEST 0

using namespace std;

ifstream f(TEST == 1 ? "test.in" : "main.in");

char opp; char res;
int sum = 0;
int main() {
    while (1) {
        f >> opp >> res;
        if (f.eof()) break;
        if (opp+23 == res) sum+=3;
        else if (res-(opp+23) == 1 || res-(opp+20)== 1) sum += 6;
        sum += res-87;
    }
    cout << sum;
}