#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

struct Packet {
    vec<Packet*> subPackets;
    int integer = -1;
    Packet(){}
    Packet(int i) {
        integer = i;
    }
};
Packet createPacket(string p) {
    Packet main;
    Packet *curr;
    stack<Packet*> s;
    s.push(&main);
    for (int i=1; i<p.size()-1; i++) {
        if (p[i] == '[') {
            s.push(new Packet());
        }
        else if (p[i] ==']') {
            curr = s.top();
            s.pop();
            if (s.size() != 0) s.top()->subPackets.push_back(curr);
        } else if (p[i] != ',' ) {
            s.top()->subPackets.push_back(new Packet(p[i]-'0'));
        }
    }
    return main;
}
void printPacket(Packet p) {
    if (p.integer != -1) {
        cout << p.integer << " ";
        return;
    } else {
        cout << "[ ";
        for (auto pac: p.subPackets) {
            printPacket(*pac);
        }
        cout << "] ";
    }

}

int compare(Packet &left, Packet &right) {
    if (left.integer != -1 && right.integer != -1){
        if (left.integer == right.integer) return -1;
        else return left.integer < right.integer;
    } else if (left.integer == -1 && right.integer == -1) {
        for (int i=0; i<left.subPackets.size(); i++) {
            int result;
            if (i > right.subPackets.size()-1) return 0;
            result = compare(*left.subPackets[i], *right.subPackets[i]);
            if (result != -1) return result;
        }
        return 1;
    } else {
        if (left.integer != -1) {
            left.subPackets.push_back(new Packet(left.integer));
            left.integer = -1;
            // return compare(*left.subPackets[0], right);
        }
        else if (right.integer != -1) {
            right.subPackets.push_back(new Packet(right.integer));
            right.integer = -1;
            // return compare(left, *right.subPackets[0]);
        }
        return compare(left, right);
    }
}

int main() {
    vec<pair<Packet, Packet>> indices;

    string left, right;
    int sum = 0;
    int index = 1;
    while (true) {
        f >> left >> right; // stuck on left side ran out of items, continue testing with pair 7 (segfault because of empty packets) 
                            // (1, 2, 3, 4, 5, 6 pass)
        indices.push_back(make_pair(createPacket(left), createPacket(right)));
        if (compare(indices[index-1].first, indices[index-1].second) == 1) {
            sum += index;
        }
        index++;
        if (f.eof()) break;
    }
    cout << sum << endl;
    printPacket(indices[7].second);
}
