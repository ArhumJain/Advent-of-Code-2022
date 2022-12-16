#include "../utils/advent.h"

using namespace aoc;
using CoordPair = pair<pair<long, long>, pair<long, long>>;

constexpr int TEST = 0;
constexpr long BOUND = 4000000;
F f(TEST == 1 ? "test.in" : "main.in");

inline long manDist(int x1, int y1, int x2, int y2) {return abs(x1-x2) + abs(y1-y2);}

long overlapCount(vec<CoordPair> &sensors, long ROW, vec<pair<int,int>> &r) {
        vec<pair<int,int>> ranges;
        int mhatDist;
        int midLength;
        pair<int, int> range;
        for (CoordPair &p: sensors) {
            mhatDist = manDist(p.first.first, p.first.second, p.second.first, p.second.second);
            midLength = mhatDist - abs(p.first.second-ROW);
            if (midLength < 0) continue;
            range.first = p.first.first - midLength;
            range.second = p.first.first + midLength;
            if (range.first < 0) range.first = 0;
            if (range.second > BOUND) range.second = BOUND;
            ranges.push_back(range);
        }
        sort(ranges.begin(), ranges.end());
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
        r = ranges;
        return sum;
}
int main() {
    vec<CoordPair> sensors;
    CoordPair r;
    while (true) {
        f >> r.first.first >> r.first.second >> r.second.first >> r.second.second;
        sensors.push_back(r);
        if (f.eof()) break;
    }
    long minimum = BOUND;
    vec<pair<int, int>> ranges;
    for (size_t y=0; y<=BOUND; y++) {
        if (overlapCount(sensors, y, ranges) < BOUND) {
            cout << "X: " << ranges[1].first-1 << endl;
            cout << "Y: " << y << endl;
            break;
        }
    }
}