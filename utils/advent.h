#include <bits/stdc++.h>

using namespace std;

namespace aoc {
    using F = ifstream;
    template <typename T>
    using vec2d = vector<vector<T>>;

    template<typename T>
    using vec = vector<T>;

    template<typename T1, typename T2>
    using umap = unordered_map<T1, T2>;

    template<typename T>
    using uset = unordered_set<T>;

    template <typename T> 
    void print1d(vector<T> &v) {
        for (T i: v) cout << i << endl;
    }

    template <typename T> 
    void print2d(vector<vector<T>> &v) {
        for (auto _: v) {
            for(T i: _) cout << i << " ";
            cout << endl;
        }
    }
}