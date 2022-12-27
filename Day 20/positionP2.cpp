#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

struct Node {
    int shiftCount = -1;
    ll shift;
    Node *next = nullptr;
    Node (ll s) {
        shift = s;
    }
};

int getShiftedPos(ll shift, ll currPos, ll size) {
    if (sign(shift)) {
        return (currPos + shift)%(size-1);
    } else {
        return (size-1) - ((((size-1) - currPos) + abs(shift))%(size-1));
    }
}

void shift(int currPos, int newPos, vector<Node*> &numbers) {
    if (currPos > newPos) rotate(numbers.rend()-currPos-1,numbers.rend()-currPos,numbers.rend()-newPos);
    else rotate(numbers.begin()+currPos,numbers.begin()+currPos+1,numbers.begin()+newPos+1);
}

int main() {
    vec<string> r = readlines(f);
    Node *last = new Node(stoi(r[0])*static_cast<ll>(811589153));
    vec<Node*> numbers = {last};
    Node *first = numbers[0];
    Node *curr = first;
    Node *zero;
    for_each(r.begin()+1, r.end(), [=, &numbers, &last, &zero] (string &s) {
        last->next = new Node(stoi(s)*static_cast<ll>(811589153));
        numbers.push_back(last->next);
        last = last->next;
        if (last->shift == 0) zero = last;
    });
    int currPos;
    for (int i=0; i<10; i++) {
        while (curr != nullptr) {
            if (curr->shiftCount == i) {
                curr = curr->next;
                continue;
            }
            currPos = distance(numbers.begin(), find(numbers.begin(), numbers.end(), (curr)));
            shift(currPos, getShiftedPos(curr->shift, currPos, numbers.size()), numbers);
            curr->shiftCount++;
            curr = curr->next;
        }
        curr = first;
    }
    int zeroPos = distance(numbers.begin(), find(numbers.begin(), numbers.end(), (zero)));
    cout << numbers[(zeroPos+1000)%(numbers.size())]->shift + 
            numbers[(zeroPos+2000)%(numbers.size())]->shift + 
            numbers[(zeroPos+3000)%(numbers.size())]->shift << endl;
}
