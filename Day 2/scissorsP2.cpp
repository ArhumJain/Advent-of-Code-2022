#include "../advent.h"

#define TEST 0

RFILE f(TEST == 1 ? "test.in" : "main.in");

int sum = 0;
char opp, res;
int main() {
    while (1) {
        f >> opp >> res;
        if (f.eof()) break;
        sum += (res-88)*3;
        if (res == 88) sum += ((opp-66)%3 > -1 ? (opp-66)%3 : 2)+1;
        else if (res==89) sum += opp-64;
        else if (res==90) sum += (opp-64)%3+1;
    }
    cout << sum;
}