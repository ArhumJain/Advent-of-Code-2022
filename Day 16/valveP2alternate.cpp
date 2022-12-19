
#include "../utils/advent.h"

using namespace aoc; // Untested if this actually gives the right result.
                    // Wrote it while original part 2 was running in the background for 3 hours and
                    // it ended up giving the right answer.

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

int bfs(string valve, string targetValve, map<string, Valve> &valves) {
    string curr = valve;
    int currLevel = 0;
    queue<pair<string, int>> q;
    map<string, bool> explored {{curr,true}};
    string neighbor;
    while (curr != targetValve) {
        for (string id: valves[curr].leads) {
            if (!explored[id]) {
                neighbor = id;
                explored[neighbor] = true;
                q.push(make_pair(neighbor, currLevel+1));
            }
        }
        curr = q.front().first;
        currLevel = q.front().second;
        q.pop();
    }
    return currLevel;
}

inline int updatedPressure(int pressure, string valve, int minutes, map<string, Valve> &valves) {
    return pressure + (valves[valve].rate * (26-(minutes)));
}
int c = 0;
map<tuple<int, int, int, int, int>, int> state;
int recurse(string valve, string valveEl, int pressure, int pressureEl, int mnt, int mntEl, int onCount, int maxOn,
            map<string, Valve> &valves, map<string, vector<pair<string, int>>> &graph) 
{
    if (onCount == maxOn || (mnt == 26 && mntEl == 26)) {
        c++;
        return pressure + pressureEl;
    }
    else if (state[{pressure, pressureEl, mnt, mntEl, onCount}] != 0) {
        return state[{pressure, pressureEl, mnt, mntEl, onCount}]; 
    }
    int m = -1;
    string nextValve = valve;
    string nextValveEl = valveEl;
    int nextPressure = pressure;
    int nextPressureEl = pressureEl;
    int nextMnt = mnt;
    int nextMntEl = mntEl;

    bool nextValveSwitched = false;
    bool nextValveElSwitched = false;

    bool timeOut = true;
    bool timeOutEl = true;
    for (auto &connection: graph[valve]) {
        if (valves[connection.first].on == false && connection.second <= 26-mnt) {
            timeOutEl = false;
            valves[connection.first].on = true;
            nextValveSwitched = true;
            nextValve = connection.first;
            nextPressure = updatedPressure(pressure, nextValve, mnt+connection.second, valves);
            nextMnt += connection.second;
        }
        for (auto &connectionEl: graph[valveEl]) {
            if (valves[connectionEl.first].on == false && connectionEl.second <= 26-mntEl) {
                valves[connectionEl.first].on = true;
                timeOutEl = false;
                nextValveElSwitched = true;
                nextValveEl = connectionEl.first;
                nextPressureEl = updatedPressure(pressureEl, nextValveEl, mntEl+connectionEl.second, valves);
                nextMntEl += connectionEl.second;

            }
            if (nextValve == valve && nextValveEl == valveEl) continue;
            m = max(m, recurse(nextValve, nextValveEl, nextPressure, nextPressureEl, nextMnt, nextMntEl,
                           onCount + nextValveSwitched + nextValveElSwitched, maxOn, valves, graph));
            if (nextValveElSwitched) {
                valves[connectionEl.first].on = false;
            }
            nextValveElSwitched = false;
            nextValveEl = valveEl;
            nextPressureEl = pressureEl;
            nextMntEl = mntEl;
        }
        if (nextValveSwitched) {
            valves[connection.first].on = false;
        }
        nextValveSwitched = false;
        nextValve = valve;
        nextPressure = pressure;
        nextMnt = mnt;
    }
    if (timeOut && timeOutEl) m = pressure + pressureEl;

    state[{pressure, pressureEl, mnt, mntEl, onCount}] = m;
    if (m > 2419) {
        cout << m  << endl;
    }
    return m; 
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
    map<string, vector<pair<string, int>>> graph;
    for (auto &v: valves) {
        for (auto &t: valves) {
            if ((t.first != v.first && t.second.rate != 0 && v.second.rate != 0) || (v.first == "AA" && t.first != "AA" & t.second.rate != 0)) {
                graph[v.first].push_back(make_pair(t.first, bfs(v.first, t.first, valves)+1));
            }
        } 
    }
    cout << recurse("AA", "AA", 0, 0, 0, 0, 0, maxOn, valves, graph) << endl;
    cout << "Done." << endl;
}