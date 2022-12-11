#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

struct Monkey {
    vector<unsigned long long int> items;
    string op;
    string opVal;
    int divisor;
    int inspect = 0;
    Monkey *trueM;
    Monkey *falseM;

    unsigned long long int operate(unsigned long long int level) {
        unsigned long long int val = opVal == "old" ? level : stoi(opVal);
        return op == "+" ? level + val : level * val;
    }
};
int main() {
    vec<Monkey> monkeys(4);
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
    for (int round = 0; round < 10000; round++) {
        if (round == 19) {
            cout << "hi " << endl;
        }
        for (int i=0; i<monkeys.size(); i++) {
            for (int item: monkeys[i].items) {
                if (monkeys[i].operate(item) % monkeys[i].divisor == 0) {
                    monkeys[i].trueM->items.push_back(monkeys[i].operate(item));
                } else monkeys[i].falseM->items.push_back(monkeys[i].operate(item));
                monkeys[i].inspect++;
            }
            monkeys[i].items.clear();
        }
    }
    sort(monkeys.begin(), monkeys.end(), [] (const Monkey &a, const Monkey &b) { return a.inspect > b.inspect; });
    cout << monkeys[0].inspect << endl;
    cout << monkeys[1].inspect << endl;
    cout << (long)(monkeys[0].inspect * monkeys[1].inspect);
}
