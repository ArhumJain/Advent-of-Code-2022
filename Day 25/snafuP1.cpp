#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

int main() {
    map<char, int> toInt = {{'=', -2}, {'-', -1}, {'0', 0}, {'1', 1}, {'2', 2}};
    map<int, char> toChar = {{-2, '='}, {-1, '-'}, {0, '0'}, {1, '1'}, {2, '2'}};
    vec2d<int> numbers;
    string r;
    int maxSize = -1;
    while (true) {
         f >> r;
         numbers.push_back(vec<int>());
         for (int i=r.size()-1; i > -1; i--) {
            numbers[numbers.size()-1].push_back(toInt[r[i]]);
         }
         maxSize = max(maxSize, static_cast<int>(r.size()));
         if (f.eof()) break;
    }
    for (vec<int> &number: numbers) {
        for (int i=0; i<maxSize+1; i++) {
            if (i >= number.size()) number.push_back(0);
        }
    }
    vec<int> sum = numbers[0];
    vec<int> number;
    for (int i=1; i<numbers.size(); i++) {
        number = numbers[i];
        for (int p=0; p<maxSize+1; p++) {
            if (sum[p]+number[p] >= 3) {
                sum[p] = -2 + (sum[p]+number[p]-3);
                sum[p+1]++;
            } else if (sum[p]+number[p] <= -3) {
                sum[p] = 2 + (sum[p]+number[p]+3);
                sum[p+1]--;
            }
            else sum[p] += number[p];
        }
        if (sum.size() == maxSize-3) sum.push_back(0);
    }
    for (int i=sum.size()-1; i > -1; i--) cout << toChar[sum[i]];

}