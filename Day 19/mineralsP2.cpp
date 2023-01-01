#include "../utils/advent.h"

using namespace aoc;
using State = tuple<int,int,int,int,int,int,int,int,int>;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

enum Resource { ORE, CLAY, OBBY, GEO };

map<State, int> states;

inline int optimalGeoGenerated(int minutes) { return ((minutes-1)*(minutes))/2; }

int getGeodeMax(vec<int> resourceCounts, vec<int> robotCounts, vec<array<int, 3>> &robotCosts, vec<int> &maxResCosts, int minutes, int &currGeoMax, array<bool, 4> allowed) {
    if (minutes == 33) return max(resourceCounts[GEO], currGeoMax);
    if (resourceCounts[GEO]+robotCounts[GEO]*(33-minutes)+optimalGeoGenerated(minutes-33) <= currGeoMax) return currGeoMax;
    array<bool, 4> robotsToBuild = {false,false,false,false};
    for (int i=3; i > -1; i--) {
        if (robotCounts[i] >= maxResCosts[i]) continue;
        if (robotCosts[i][ORE] <= resourceCounts[ORE]
            && robotCosts[i][CLAY] <= resourceCounts[CLAY]
            && robotCosts[i][OBBY] <= resourceCounts[OBBY] && !allowed[i])
        {
            robotsToBuild[i] = true;
            if (i == 3) break;
        }
    }

    for (int i=0; i<4; i++) resourceCounts[i] += robotCounts[i];

    int geodes = -1;
    for (int i=0; i<4; i++) {
        robotCounts[i]++;
        if (robotsToBuild[i]) {
            geodes = max(geodes, getGeodeMax(
                {resourceCounts[ORE]-robotCosts[i][ORE], resourceCounts[CLAY]-robotCosts[i][CLAY], resourceCounts[OBBY]-robotCosts[i][OBBY], resourceCounts[GEO]},
                robotCounts,
                robotCosts,
                maxResCosts,
                minutes+1,
                currGeoMax,
                {false,false,false,false}
            ));
        }
        robotCounts[i]--;
    }
    geodes = max(geodes, getGeodeMax(resourceCounts, robotCounts, robotCosts, maxResCosts, minutes+1, currGeoMax, robotsToBuild));
    currGeoMax = max(geodes, currGeoMax);
    return geodes;
}

string r;
vec<string> rVec;

// 0: Ore, 1: Clay, 2: Obby, 3: Geode
vec<array<int, 3>> robotCosts(4, {0, 0, 0});
vec<int> resourceCounts;
vec<int> robotCounts;
vec<int> maxResCosts;
int id = 1;
int product = 1;
int quality;
int currGeoMax;

int main()
{
    while (true)
    {
        if (id == 4) break;
        currGeoMax = -1;
        getline(f, r);
        rVec = split(r, " ");
        resourceCounts = {0, 0, 0, 0};
        robotCounts = {1, 0, 0, 0};
        maxResCosts = {0,0,0,99};
        robotCosts[ORE] = {stoi(rVec[6]), 0, 0};
        robotCosts[CLAY] = {stoi(rVec[12]), 0, 0};
        robotCosts[OBBY] = {stoi(rVec[18]), stoi(rVec[21]), 0};
        robotCosts[GEO] = {stoi(rVec[27]), 0, stoi(rVec[30])};
        for (int i=0; i<4; i++) {
            for (int j=0; j<3; j++) {
                maxResCosts[j] = max(maxResCosts[j], (robotCosts[i][j]));
            }
        }
        quality = getGeodeMax(resourceCounts, robotCounts, robotCosts, maxResCosts, 1, currGeoMax, {false,false,false,false});
        product *= quality;
        id++;
        if (f.eof()) break;
    }
    cout << product << endl;
    return 1;
}
