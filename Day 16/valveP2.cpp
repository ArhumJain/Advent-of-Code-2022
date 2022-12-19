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
};

map<tuple<string, string, int, int>, int> state;
inline int lifePressure(int pressure, string valve, int minutes, map<string, Valve> &valves) {
    return pressure + (valves[valve].rate * (26-(minutes+1)));
}
int c = 0;
int recurse(string valveM, string valveEle, int pressureM, int pressureEle, int minutes, int &m, map<string, Valve> &valves, string prevM, string prevEle, int turnedOn, int maxOn) {
    if (minutes == 26 || turnedOn == maxOn) {
        return pressureM + pressureEle;
    }
    else if (state[{valveM, valveEle, pressureM+pressureEle, minutes}] > 0) {
        return state[{valveM, valveEle, pressureM+pressureEle, minutes}];
    } 
    int localMax = -1;
    if (!valves[valveM].on && !valves[valveEle].on && valves[valveM].rate != 0 && valves[valveEle].rate != 0 && valveM != valveEle) {
        valves[valveM].on = true;
        valves[valveEle].on = true;
        localMax = max(localMax,recurse(valveM,valveEle,lifePressure(pressureM,valveM,minutes,valves),lifePressure(pressureEle,valveEle,minutes,valves), 
                                         minutes+1, m, valves, valveM, valveEle, turnedOn+2, maxOn)); 
        valves[valveM].on = false;
        valves[valveEle].on = false;
    }
    if (!valves[valveM].on && valves[valveM].rate != 0) {
        valves[valveM].on = true;
        for (auto v: valves[valveEle].leads) {
            localMax = max(localMax,recurse(valveM,v,lifePressure(pressureM,valveM,minutes,valves),pressureEle,minutes+1,m,valves,valveM,valveEle,turnedOn+1,maxOn));
        }
        valves[valveM].on = false;
    }
    else if (!valves[valveEle].on && valves[valveEle].rate != 0) {
        valves[valveEle].on = true;
        for (auto v: valves[valveM].leads) {
            localMax = max(localMax,recurse(v, valveEle, pressureM,lifePressure(pressureEle,valveEle,minutes,valves),minutes+1,m,valves,valveM,valveEle,turnedOn+1,maxOn));
        }
        valves[valveEle].on = false;
    }
    for (auto me: valves[valveM].leads) {
        if (me != prevM){
            for (auto ele: valves[valveEle].leads) {
                if (ele != prevEle && (ele != me)) {
                    localMax = max(localMax, recurse(me, ele, pressureM, pressureEle, minutes+1, m, valves, valveM, valveEle, turnedOn, maxOn));
                }
            }
        }
    }
    state[{valveM, valveEle, pressureM+pressureEle, minutes}] = localMax;
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
    cout << recurse("AA","AA",0,0,0,m,valves,"", "", 0, maxOn) << endl;
}