#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

struct Valve {
    string id;
    int rate;
    bool on = false;
    vec<string> leads;

    Valve() {};
    Valve(string i, int r) {
        id = i; rate = r; 
    }
    const bool operator==(const Valve &other) {
        return other.id == this->id;
    }
};

void recurse(string valve, int pressure, int minutes, int &m, map<string, Valve> &valves) {
    if (minutes == 30) {
        m = max(m, pressure);
        cout << m << endl;
        return;
    }
    // cout << "hi" <<endl;
    if (valves[valve].on == false && valves[valve].rate != 0) {
            valves[valve].on = true;
            recurse(valve, pressure+(valves[valve].rate * (30-(minutes+1))), minutes+1, m, valves);
            valves[valve].on = false;
    }
    for (auto v: valves[valve].leads) {
        recurse(v, pressure, minutes+1, m, valves);
    }
    // return pressure;
    return;
}
map<string, Valve> valves;
int main() { 
    string r;
    string id;
    while (true) {
        getline(f, r);
        id = r.substr(6,2);
        cout << r.substr(23, r.find(';')-23) << endl;
        valves[id] = Valve(id, stoi(r.substr(23, r.find(';')-23)));
        for (auto i: split(r.substr(r.find(";")+1, r.size()), ", ")) {
            valves[id].leads.push_back(i);
        }
        if (f.eof()) break;
    }
    int m = -1;
    recurse("AA", 0, 0, m, valves);

}