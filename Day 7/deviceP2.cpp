#include "../utils/advent.h"

using namespace aoc;

constexpr int TEST = 0;
F f(TEST == 1 ? "test.in" : "main.in");

struct Directory {
	umap<string, Directory *> dirs;
	umap<string, int> files;
	string name;
	int size = 0;
	Directory *parent;

	void increaseSize(int size) {
		this->size += size;
		if (parent != nullptr) this->parent->increaseSize(size);
	}
	Directory(string name, Directory *parent) {
		this->name = name;
		this->parent = parent;
	}
};

void sum(Directory *root, Directory &minDir, int &needed) {
	if (root->size >= needed && root->size < minDir.size) minDir = *(root);
	if (root->dirs.size() != 0) {
        for (auto i : root->dirs) {
            sum(i.second, minDir, needed);
        }
    }
}

string first;
string second;
int main() {
	Directory *currDir = new Directory("/", nullptr);
	Directory *root = currDir;
	bool listing = false;
	while (true) {
		f >> first;
		if (first == "$") {
			f >> first;
			if (first == "cd") {
				f >> first;
				if (first == "..") currDir = currDir->parent;
				else {
					if (currDir->dirs[first] == nullptr) currDir->dirs[first] = new Directory(first, currDir);
					currDir = currDir->dirs[first];
				}
			}
		}
		else if (first == "dir") {
			f >> first;
			if (currDir->dirs[first] == nullptr) currDir->dirs[first] = new Directory(first, currDir);
		}
		else {
			f >> second;
			currDir->files[second] = stoi(first);
			currDir->increaseSize(stoi(first));
		}
		if (f.eof()) break;
	}
    Directory minDir = *(root);
    int needed = 30000000 - (70000000 - (root->size));
	sum(root, minDir, needed);
    cout << minDir.size;
}