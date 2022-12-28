#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

enum Type { NUMBER, MATH };
struct Job {
    static map<string, Job> monkeys;
    Type t;
    ll n;
    string m1;
    string m2;
    char operate;
    Job () {};
    Job (ll a) {
        n = a;
        t = Type::NUMBER;
    }
    Job (string a, string b, char op) {
        m1 = a;
        m2 = b;
        operate = op;
        t = Type::MATH;
    }

    ll solveX(ll targetVal) {
        if (this->n == -1) {
            return targetVal;
        }
        ll subTarget;
        ll a = Job::monkeys[m1].getVal();
        ll b = Job::monkeys[m2].getVal();
        if (a == -1) {
            switch (operate) {
                case '=': subTarget = b; break;
                case '-': subTarget = b + targetVal; break;
                case '+': subTarget = targetVal-b; break;
                case '*': subTarget = targetVal/b; break;
                case '/': subTarget = targetVal * b; break;
            }
            return Job::monkeys[m1].solveX(subTarget);
        } else {
            switch (operate) {
                case '=': subTarget = b; break; 
                case '-': subTarget = a-targetVal; break;
                case '+': subTarget = targetVal-a; break;
                case '*': subTarget = targetVal/a; break;
                case '/': subTarget = a/targetVal; break;
            }
            return Job::monkeys[m2].solveX(subTarget);
        }

    }

    ll getVal() {
        if (this->t == Type::NUMBER) return n;
        else {
            ll a = monkeys[m1].getVal();
            ll b = monkeys[m2].getVal();
            switch (operate) {
                case '+': return a == -1 || b == -1 ? -1 : a + b;
                case '-': return a == -1 || b == -1 ? -1 : a - b;
                case '*': return a == -1 || b == -1 ? -1 : a * b;
                case '/': return a == -1 || b == -1 ? -1 : a / b;
            }
        }
    }
};
map<string, Job> Job::monkeys;
int main() {
    string _;
    vec<string> r;
    while (true) {
        getline(f, _);
        r = split(_);
        if (r.size() == 2) Job::monkeys[r[0]] = Job(stoll(r[1]));
        else Job::monkeys[r[0]] = Job(r[1],r[3],r[2][0]);
        if (f.eof()) break;
    }
    Job::monkeys["root"].operate = '=';
    Job::monkeys["humn"].n = -1;
    cout << Job::monkeys["root"].solveX(1);
}
