#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
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
};

map<tuple<string, int, int>, int> state;
int recurse(string valve, int pressure, int minutes, int &m, map<string, Valve> &valves, string prev) {
    if (minutes == 30) return pressure;
    else if (state[{valve, pressure, minutes}] != 0) return state[{valve, pressure, minutes}];
    int localMax = -1;
    if (valves[valve].on == false && valves[valve].rate != 0) {
        valves[valve].on = true;
        localMax = max(localMax, recurse(valve, pressure+(valves[valve].rate * (30-(minutes+1))), minutes+1, m, valves, valve));
        valves[valve].on = false;
    }
    for (auto v: valves[valve].leads) { // and valve not equal to prev
        if (v != prev) localMax = max(localMax, recurse(v, pressure, minutes+1, m, valves, valve));
    }
    state[make_tuple(valve, pressure, minutes)] = localMax;
    return localMax;
}

int main() { 
    map<string, Valve> valves;
    string r;
    string id;
    int maxOn = 0;
    while (true) {
        getline(f, r);
        id = r.substr(6,2);
        valves[id] = Valve(id, stoi(r.substr(23, r.find(';')-23)));
        for (auto i: split(r.substr(r.find(";")+1, r.size()), ", ")) {
            valves[id].leads.push_back(i);
        }
        if (valves[id].rate != 0) maxOn++;
        if (f.eof()) break;
    }
    for (auto &pair: valves) {
        sort(valves[pair.first].leads.begin(), valves[pair.first].leads.end(), [&valves] (const string v1, const string v2) {return valves[v1].rate > valves[v2].rate;});
    }
    int m = -1;
    cout << recurse("AA", 0, 0, m, valves, "") << endl;
}