#include "../utils/advent.h"

using namespace aoc;
using CoordPair = pair<pair<long, long>, pair<long, long>>;

constexpr int TEST = 0;
constexpr int ROW = 2000000;
F f(TEST == 1 ? "test.in" : "main.in");

inline long manDist(int x1, int y1, int x2, int y2) {return abs(x1-x2) + abs(y1-y2);}

int main() {
    vec<CoordPair> sensors;
    vec<pair<int,int>> ranges;
    CoordPair r;
    while (true) {
        f >> r.first.first >> r.first.second >> r.second.first >> r.second.second;
        sensors.push_back(r);
        if (f.eof()) break;
    }
    int mhatDist;
    int midLength;
    pair<int, int> range;
    for (CoordPair &p: sensors) {
        mhatDist = manDist(p.first.first, p.first.second, p.second.first, p.second.second);
        midLength = mhatDist - abs(p.first.second-ROW);
        if (midLength < 0) continue;
        range.first = p.first.first - midLength;
        range.second = p.first.first + midLength;
        ranges.push_back(range);
    }
    sort(ranges.begin(), ranges.end(), [] (pair<int, int> &p1, pair<int, int> &p2) {return p1.first < p2.first;});
    vec<CoordPair> finalSegments;
    for (int i=0; i<ranges.size()-1; i++) {
        if (ranges[i+1].first <= ranges[i].second) {
            ranges[i+1].first = min(ranges[i+1].first, ranges[i].first);
            ranges[i+1].second = max(ranges[i+1].second, ranges[i].second);
            ranges.erase(ranges.begin()+i);
            i--;
        }
    }
    int sum = 0;
    for (auto &segment: ranges) sum += (segment.second - segment.first);
    cout << sum;
}