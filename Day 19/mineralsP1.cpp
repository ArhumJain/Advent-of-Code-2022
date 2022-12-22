#include "../utils/advent.h"

using namespace aoc;
// using State = tuple<int,int,int,int,int,int,int,int,int>;
// using State = tuple<int,int,int,int, int>;
// using State = tuple<int,int,int>;
using State = tuple<int,int,int,int,int,int,int>;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

enum RobotType {
    ORE, CLAY, OBBY, GEO
};

struct Blueprint {
    // 0: Ore, 1: Clay, 2: Obsidian
    map<string, vector<int>> robotCosts;
    int oreAmount = 0;
    int clayAmount = 0;
    int obbyAmount = 0;

    int oreRobCount = 1;
    int clayRobCount = 0;
    int obbyRobCount = 0;
};

struct Robot {
    RobotType type;
    int construction = 2;
};

// We want to check if we have resources to build any robots
// Add those to robots to possible constructions
// Loop through existing robots and add their resources
// For every possible construction, call findQuality
// Call findQuality with no construction
map<State, int> states;
bool check = false;
int getRobotToConstruct(int currRobot, vec<int> &resourceCounts, vec<int> &robotCounts, vec<array<int, 3>> &robotCosts) {
    for (int i=2; i > -1; i--) {
        if (robotCosts[currRobot][i] > resourceCounts[i]) {
            return currRobot == 0 ? -1 : getRobotToConstruct(i, resourceCounts, robotCounts, robotCosts);
        }
    }
    return currRobot;
    // return getRobotToConstruct(currRobot-1, resourceCounts, robotCounts, robotCosts);
}
int findQuality(vec<int> resourceCounts, vec<int> robotCounts, vec<array<int, 3>> &robotCosts, int minutes) 
{

    if (minutes == 26) {
        // for (int i=0; i<4; i++) {
        //     resourceCounts[i] += robotCounts[i];
        // }

        // if (resourceCounts[GEO] > 10) {
        //     cout >> "Greater than 10" >> endl;
        // }
        return resourceCounts[GEO];
    }
    // State s = {resourceCounts[ORE], resourceCounts[CLAY], resourceCounts[OBBY], resourceCounts[GEO],
    //             robotCounts[ORE], robotCounts[CLAY], robotCounts[OBBY], robotCounts[GEO], minutes};
    // State s = {robotCounts[ORE], robotCounts[CLAY], robotCounts[OBBY], robotCounts[GEO], minutes};
    // State s = {accumulate(resourceCounts.begin(), resourceCounts.end(), 0), accumulate(robotCounts.begin(), robotCounts.end(), 0), minutes};
    State s = {resourceCounts[ORE], resourceCounts[CLAY], resourceCounts[OBBY],
                robotCounts[ORE], robotCounts[CLAY], robotCounts[OBBY], minutes};
    if (states[s] != 0) { 
        return states[s];
    }
    int maxQuality = -1;
    bool constructRobots[4] = {false, false, false, false};
    int robotToConstruct = -1;
    // robotToConstruct = getRobotToConstruct(3, resourceCounts, robotCounts, robotCosts);
    
    for (int i=3; i>-1; i--) {
        if (robotCosts[i][ORE] <= resourceCounts[ORE] 
            && robotCosts[i][CLAY] <= resourceCounts[CLAY] 
            && robotCosts[i][OBBY] <= resourceCounts[OBBY])
        {
            // if (check) {
            //     cout << get<ORE>(robotCosts[i]) << " " << resourceCounts[ORE] << endl;
            //     cout << get<CLAY>(robotCosts[i]) << " " << resourceCounts[CLAY] << endl;
            //     cout << get<OBBY>(robotCosts[i]) << " " << resourceCounts[OBBY] << endl;
            // }

            // robotToConstruct = i;
            // break;
            constructRobots[i] = true;
        }
    }

    for (int i=0; i<4; i++) {
        // if (i == 3 && robotCounts[i] > 0) {
        //     cout << " hi"<< endl;
        // }
        resourceCounts[i] += robotCounts[i];
    }

    maxQuality = max(findQuality(resourceCounts, robotCounts, robotCosts, minutes+1), maxQuality);
    // if (robotToConstruct != -1){
    //     // if (robotToConstruct == 3) {
    //     //     cout << "test" << endl;
    //     // }
    //     robotCounts[robotToConstruct] = robotCounts[robotToConstruct]+1;
    //     maxQuality = max(findQuality(
    //         {resourceCounts[ORE]-robotCosts[robotToConstruct][ORE], resourceCounts[CLAY]-robotCosts[robotToConstruct][CLAY], resourceCounts[OBBY]-robotCosts[robotToConstruct][OBBY], resourceCounts[GEO]},
    //         robotCounts,
    //         robotCosts,
    //         minutes+1
    //     ), maxQuality);
    //     // robotCounts[robotToConstruct]--;
    //     robotCounts[robotToConstruct] = robotCounts[robotToConstruct]-1;
    // }


    for (int i=3; i> -1; i--) {
        if (constructRobots[i]) {
            robotCounts[i]++;
            maxQuality = max(findQuality(
                {resourceCounts[ORE]-robotCosts[i][ORE], resourceCounts[CLAY]-robotCosts[i][CLAY], resourceCounts[OBBY]-robotCosts[i][OBBY], resourceCounts[GEO]},
                robotCounts,
                robotCosts,
                minutes+1
            ), maxQuality);
            robotCounts[i]--;
            // break;
        }
    }

    states[s] = maxQuality;
    if (maxQuality == -1) cout << "this should not be happening" << endl;
    return maxQuality;

}

string r;
vec<string> rVec;

// 0: Ore, 1: Clay, 2: Obby, 3: Geode
vec<array<int, 3>> robotCosts(4, {0,0,0});
vec<int> resourceCounts;
vec<int> robotCounts;
int id = 1;
int sum = 0;
int quality;
int main() {
    while(true) {
        getline(f, r);
        rVec = split(r, " ");
        resourceCounts = {0,0,0,0};
        robotCounts = {1,0,0,0};
        robotCosts[ORE] = {stoi(rVec[6]),0,0};
        robotCosts[CLAY] = {stoi(rVec[12]),0,0};
        robotCosts[OBBY] = {stoi(rVec[18]), stoi(rVec[21]), 0};
        robotCosts[GEO] = {stoi(rVec[27]), 0, stoi(rVec[30])};

        quality = findQuality(resourceCounts, robotCounts, robotCosts, 1);
        check = true;
        printf("ID %i, Quality: %i\n", id, quality);
        sum += id * quality;
        printf("Sum: %i\n", sum);
        states.clear();
        // cout << sum << endl;
        id++;
        if (f.eof()) break;
    }
}
