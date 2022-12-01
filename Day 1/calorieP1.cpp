#include <iostream>
#include <fstream>

#define TEST 0

using namespace std;



ifstream f(TEST == 1 ? "test.in" : "main.in");
int MAX = -1; int sum = 0; string a = "";
int main() {
    while (!f.eof()) {
        f >> a;
        if (a == ".") { 
            if (sum > MAX) MAX = sum; 
            sum = 0;
        }
        else sum += stoi(a); 
    }
    std::cout << MAX << endl;

}
