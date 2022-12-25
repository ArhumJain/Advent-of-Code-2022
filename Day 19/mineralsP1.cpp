#include "../utils/advent.h"

using namespace aoc;
using State = tuple<int,int,int,int,int,int,int,int,int>;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

enum Resource
{
    ORE,
    CLAY,
    OBBY,
    GEO
};

map<State, int> states;

inline int optimalGeoGenerated(int minutes) {
    return ((minutes-1)*(minutes))/2;
}
int findQuality(vec<int> resourceCounts, vec<int> robotCounts, vec<array<int, 3>> &robotCosts,
                vec<int> &maxResCost, int minutes, int &currGeoMax)
{
    if (minutes == 25)
    {
        return resourceCounts[GEO];
    }
    State s = {resourceCounts[ORE], resourceCounts[CLAY], resourceCounts[OBBY], resourceCounts[GEO],
                robotCounts[ORE], robotCounts[CLAY], robotCounts[OBBY], robotCounts[GEO], minutes};

    if (states[s] != 0) {
        return states[s];
    }
    if (resourceCounts[GEO] + robotCounts[GEO]*(25-minutes) + optimalGeoGenerated(25-minutes) < currGeoMax)  {
        return states[s];
    }

    int maxQuality = -1;
    bool constructRobots[4] = {false, false, false, false};

    for (int i=3; i>-1; i--) {
        if (i != GEO && robotCounts[i] >= maxResCost[i]) {
            continue;
        }
        if (robotCosts[i][ORE] <= resourceCounts[ORE]
            && robotCosts[i][CLAY] <= resourceCounts[CLAY]
            && robotCosts[i][OBBY] <= resourceCounts[OBBY])
        {
            constructRobots[i] = true;
            if (i == GEO) break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        resourceCounts[i] += robotCounts[i];
    }

    for (int i=3; i> -1; i--) {
        if (constructRobots[i]) {
            robotCounts[i]++;
            maxQuality = max(findQuality(
                {resourceCounts[ORE]-robotCosts[i][ORE], resourceCounts[CLAY]-robotCosts[i][CLAY], resourceCounts[OBBY]-robotCosts[i][OBBY], resourceCounts[GEO]},
                robotCounts,
                robotCosts,
                maxResCost,
                minutes+1,
                currGeoMax
            ), maxQuality);
            robotCounts[i]--;
        }
    }
    maxQuality = max(findQuality(resourceCounts, robotCounts, robotCosts, maxResCost, minutes + 1, currGeoMax), maxQuality);
    currGeoMax = max(currGeoMax, maxQuality);
    states[s] = maxQuality;
    return maxQuality;
}

string r;
vec<string> rVec;

// 0: Ore, 1: Clay, 2: Obby, 3: Geode
vec<array<int, 3>> robotCosts(4, {0, 0, 0});
vec<int> resourceCounts;
vec<int> robotCounts;
vec<int> maxResCosts;
int id = 1;
int sum = 0;
int quality;
int currGeoMax;
int main()
{
    while (true)
    {
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
        quality = findQuality(resourceCounts, robotCounts, robotCosts, maxResCosts, 1, currGeoMax);
        printf("ID %i, Quality: %i\n", id, quality);
        sum += id * (quality);
        printf("Sum: %i\n", sum);
        states.clear();
        id++;
        if (f.eof()) break;
    }
}




