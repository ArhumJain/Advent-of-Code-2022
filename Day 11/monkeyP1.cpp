#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

struct Monkey {
    vector<int> items;
    string op;
    string opVal;
    int divisor;
    int inspect = 0;
    Monkey *trueM;
    Monkey *falseM;

    int operate(int level) {
        int val = opVal == "old" ? level : stoi(opVal);
        return op == "+" ? level + val : level * val;
    }
};
int main() {
    vec<Monkey> monkeys(8);
    string s;
    string _;
    for (int i=0; i<monkeys.size(); i++) {
        getline(f, s);
        getline(f, s);
        for (auto k: split(s.substr(18,s.size()), ", ")) {
            monkeys[i].items.push_back(stoi(k));
        }
        getline(f,s);
        monkeys[i].op = s[23];
        monkeys[i].opVal = s.substr(25, s.size());
        getline(f, s);
        monkeys[i].divisor = stoi(s.substr(21, s.size()));
        getline(f, s);
        monkeys[i].trueM = &monkeys[s[s.size()-1] - '0'];
        getline(f, s);
        monkeys[i].falseM = &monkeys[s[s.size()-1] - '0'];
        getline(f, s);
    }
    for (int round = 0; round < 20; round++) {
        for (int i=0; i<monkeys.size(); i++) {
            for (int item: monkeys[i].items) {
                if ((monkeys[i].operate(item) / 3) % monkeys[i].divisor == 0) {
                    monkeys[i].trueM->items.push_back(monkeys[i].operate(item)/3);
                } else monkeys[i].falseM->items.push_back(monkeys[i].operate(item)/3);
                monkeys[i].inspect++;
            }
            monkeys[i].items.clear();
        }
    }
    sort(monkeys.begin(), monkeys.end(), [] (const Monkey &a, const Monkey &b) { return a.inspect > b.inspect; });
    cout << monkeys[0].inspect * monkeys[1].inspect;
}
