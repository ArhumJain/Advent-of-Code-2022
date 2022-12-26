#include "../utils/advent.h"
using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

struct Node {
    int shift;
    bool last = false;
    bool front = false;
    Node *prev = nullptr;
    Node *next = nullptr;
    Node *originalNext = nullptr;
    Node(int s) {
        shift = s;
    }
    int &getVal(Node *n, int idx) {
        if (idx == 0) return n->shift;
        return getVal(n->next, idx-1);
    }
    int &operator[](int idx) {
        return getVal(this, idx);
    }

    static void print(Node *curr, ostream &os) {
        os << curr->shift << " ";
        if (curr->last) {
            return;
        }
        print(curr->next, os);
    }
    friend ostream &operator<<(ostream &os, Node *root) {
        print(root, os);
        return os;
    }
};
void shift(Node *n, Node *destination, Node **front, Node **last, int amt, bool forward) {
    if (amt == 0) {
        if (n->front) {
            n->next->front = true;
            n->front = false;
            *front = n->next;
        } else if (n->last) {
            n->prev->last = true;
            n->last = false;
            *last = n->prev;
        }
        if (forward) {
            if (destination == *last) {
                destination->next->front = false;
                n->front = true;
                *front = n;
            }
            n->prev = destination;
            destination->next->prev = n;
            n->next = destination->next;
            destination->next = n;
        } else {
            if (destination == *front) {
                destination->prev->last = false;
                n->last = true;
                *last = n;
            }
            n->prev = destination->prev;
            destination->prev->next = n;
            n->next = destination;
            destination->prev = n;
        }
        return;
    }
    forward ? shift(n, destination->next, front, last, amt-1, forward)
            : shift(n, destination->prev, front, last, amt-1, forward);
}
int main() {
    vec<string> _ = aoc::readlines(f);
    vec<int> numbers;
    Node *root = new Node(stoi(_[0]));
    Node *curr = root;
    Node *zero;
    Node *last;
    for_each(_.begin()+1, _.end(), [&] (string &s) {
        curr->next = new Node(stoi(s));
        curr->originalNext = curr->next;
        curr->next->prev = curr;
        curr = curr->next;
        if (curr->shift == 0) zero = curr;
    });
    root->front = true;
    curr->last = true;
    last = curr;
    last->next = root;
    root->prev = last;
    curr = root;
    while (curr != nullptr) {
        if (curr->shift == 0) curr = curr->originalNext;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        shift(curr, curr, &root, &last, abs(curr->shift), sign(curr->shift));
        curr = curr->originalNext;
    }
    cout << (*zero)[1000] + (*zero)[2000] + (*zero)[3000] << endl;
}