#include <iostream>
#include <fstream>
#include <numeric>

#define TEST 0

using namespace std;

ifstream f(TEST == 1 ? "test.in" : "main.in");
int sum = 0; string a = "";

int top[3] = {-1};
int main() {
    while (!f.eof()) {
        f >> a;
        if (a == ".") { 
            if (sum > top[0]){
                top[2] = top[1];
                top[1] = top[0];
                top[0] = sum;
            }
            else if (sum > top[1]) {
                top[2] = top[1];
                top[1] = sum;
            }
            else if (sum > top[2]) top[2] = sum;
            sum = 0;
        }
        else sum += stoi(a); 
    }
    cout << top[0] << endl;
    cout << top[1] << endl;
    cout << top[2] << endl;
    std::cout << accumulate(top, top+3, 0) << endl ;

}
