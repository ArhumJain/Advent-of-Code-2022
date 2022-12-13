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
    sstream a(p);
    Packet main;
    Packet *curr;
    stack<Packet*> s; s.push(&main);
    char read; int integer;
    while (true) {
        a >> read;
        if (read == '[') s.push(new Packet());
        else if (read ==']') {
            curr = s.top();
            s.pop();
            if (s.size() != 0) s.top()->subPackets.push_back(curr);
        } else if (read != ',' ) {
            a.unget(); a >> integer;
            s.top()->subPackets.push_back(new Packet(integer));
        }
        if (a.eof()) break;
    }
    return main;
}
void printPacket(Packet p) { // Helper function for debugging
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
int compare(Packet left, Packet right) {
    if (left.integer != -1 && right.integer != -1){
        if (left.integer == right.integer) return -1;
        else return left.integer < right.integer;
    }
    else if (left.integer != -1) {
        int integer = left.integer;
        left = Packet();
        left.subPackets.push_back(new Packet(integer));
    }
    else if (right.integer != -1) {
        int integer = right.integer;
        right = Packet();
        right.subPackets.push_back(new Packet(integer));
    }
    int result = -2;
    for (int i=0; i<left.subPackets.size(); i++) {
        if (i > static_cast<int>(right.subPackets.size())-1) return 0;
        result = compare(*left.subPackets[i], *right.subPackets[i]);
        if (result != -1) return result;
    }
    if (left.subPackets.size() < right.subPackets.size()) return 1;
    else return -1;
}
int main() {
    vec<Packet> packets;
    packets.push_back(createPacket("[[2]]"));
    packets.push_back(createPacket("[[6]]"));
    // vec<pair<Packet, Packet>> indices;
    // string left, right;
    // int sum = 0; int index = 1;
    string s;
    while (true) {
        f >> s; 
        // indices.push_back(make_pair(createPacket(left), createPacket(right)));
        packets.push_back(createPacket(s));
        // if (compare(indices[index-1].first, indices[index-1].second) == 1) sum += index;
        // index++;
        if (f.eof()) break;
    }
    sort(packets.begin(), packets.end(), [] (const Packet &a, const Packet &b) {return compare(a, b);});
    int key = 1;
    for (int i=0; i<packets.size(); i++) {
        if ((*packets[i].subPackets[0]).integer == 2 || (*packets[i].subPackets[0]).integer == 6) {
            key *= (i+1);
        }
        printPacket(*packets[i].subPackets[0]);
        cout << endl;
    }
    cout << key << endl;
}
