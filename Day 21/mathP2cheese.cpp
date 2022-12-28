#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

enum Type { NUMBER, MATH };
struct Job {
    static map<string, Job> monkeys;

    Type t;
    ull n = -1;
    string m1;
    string m2;
    char operate = ' ';

    Job () {};
    Job (ull a) {
        n = a;
        t = Type::NUMBER;
    }
    Job (string a, string b, char op) {
        m1 = a;
        m2 = b;
        operate = op;
        t = Type::MATH;
    }

    ull getVal() {
        if (this->t == Type::NUMBER) {
            if (this->operate == '!') {
                cout << "x";
                return 1;
            }
            // return to_string(n);
            cout << n;
            // return n;
        }
        else {
            switch (this->operate) {
                case '+':
                    cout << "(";
                    monkeys[m1].getVal();
                    cout << "+";
                    monkeys[m2].getVal();
                    cout << ")";
                    break;
                case '-':
                    cout << "(";
                    monkeys[m1].getVal();
                    cout << "-";
                    monkeys[m2].getVal();
                    cout << ")";
                    break;
                case '*':
                    cout << "(";
                    monkeys[m1].getVal();
                    cout << "*";
                    monkeys[m2].getVal();
                    cout << ")";
                    break;
                case '/':
                    cout << "(";
                    monkeys[m1].getVal();
                    cout << "/";
                    monkeys[m2].getVal();
                    cout << ")";
                    break;
                case '=':
                    cout << "(";
                    monkeys[m1].getVal();
                    cout << "=";
                    monkeys[m2].getVal();
                    cout << ")";
                    break;
            }
        }
        return -1;
    }
};
map<string, Job> Job::monkeys;

int main() {
    string _;
    vec<string> r;
    while (true) {
        getline(f, _);
        r = split(_);
        if (r.size() == 2) Job::monkeys[r[0]] = Job(stoull(r[1]));
        else Job::monkeys[r[0]] = Job(r[1],r[3],r[2][0]);
        if (f.eof()) break;
    }

    Job::monkeys["humn"].operate = '!';
    Job::monkeys["root"].operate = '=';

    Job::monkeys["root"].getVal();
}
