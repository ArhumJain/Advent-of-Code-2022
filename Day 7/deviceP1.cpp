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

void sum(Directory *root, int &total) {
	if (root->size <= 100000) total += root->size;
	if (root->dirs.size() == 0) return;
	for (auto i : root->dirs) {
		sum(i.second, total);
	}
}

string first;
string second;
int main() {
	Directory *currDir = new Directory("/", nullptr);
	Directory *root = currDir;
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
	int total = 0;
	sum(root, total);
	cout << total;
}