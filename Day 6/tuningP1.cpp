#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;
using F = ifstream;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

string buffer;
int main() {
  f >> buffer;
  string code = buffer.substr(0,4);
  for (int i=4; i<buffer.size(); i++) {
      code.erase(code.begin()); code.push_back(buffer[i]);
      if (unordered_set<char>(code.begin(), code.end()).size() == 4) { cout << i+1; break; }
  }
}
