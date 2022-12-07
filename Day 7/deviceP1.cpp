#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 1;
F f(TEST == 1 ? "test.in" : "main.in");

struct Directory {
    vec<tuple<int, string>> files;
    umap<string, Directory*> dirs;
    umap<string, int> files;
    string name;
    Directory(string name) {this->name = name;}

};

string a;
int main() {
    Directory currDir("/");
    bool listing = false;
    while (true){
        if (a == "$") {
            listing = false;

        }
    }

}
