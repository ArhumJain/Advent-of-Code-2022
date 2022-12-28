#include <bits/stdc++.h>
// #include <vector>
// #include <map>
// #include <unordered_map>
// #include <set>
// #include <unordered_set>


using namespace std;

namespace aoc {
    using F = std::ifstream;

    template <typename T>
    using vec3d = std::vector<std::vector<std::vector<T>>>;

    template <typename T>
    using vec2d = std::vector<std::vector<T>>;

    template<typename T>
    using vec = std::vector<T>;

    template<typename T1, typename T2>
    using umap = std::unordered_map<T1, T2>;

    template<typename T>
    using uset = std::unordered_set<T>;

    template<typename T1, typename T2>
    using tup = std::tuple<T1, T2>;

    using ul = unsigned long;
    using ll = long long;
    using ull = unsigned long long;

    using sstream = std::stringstream;

    template <typename T> 
    void print1d(std::vector<T> &v, string delimiter="\n") {
        for (T i: v) std::cout << i << delimiter;
    }

    template <typename T> 
    std::ostream &operator<<(ostream &o, std::vector<T> &v) {
        for_each(v.begin(), v.end(), [&](T &a){o << a << " ";});
        return o;
    }


    template <typename T> 
    void print2d(std::vector<std::vector<T>> &v, string delimitColumn=" ", string delimitRow="\n") {
        for (auto _: v) {
            for(T i: _) std::cout << i << delimitColumn;
            std::cout << delimitRow;
        }
    }

    template <typename T>
    inline bool sign(T n) {
        return n >= 0 ? true : false;
    }
    std::vector<std::string> split(std::string s, std::string d = " ") { // thanks stackoverflow!
        std::vector<std::string> sp;
        int start, end = -1*d.size();
        do {
            start = end + d.size();
            end = s.find(d, start);
            sp.push_back(s.substr(start, end-start));
        } while (end != -1);
        return sp;
    }

    string read(std::ifstream &f) {
        std::string r((std::istreambuf_iterator<char>(f)),
                            (std::istreambuf_iterator<char>()));
        return r;   
    }

    void readlines(std::ifstream &f, std::vector<std::string> &r) {
        std::string _;
        while (getline(f, _)) r.push_back(_);
    }
    
    std::vector<std::string> readlines(std::ifstream &f) {
        std::vector<std::string> lines;
        std::string r;
        while (getline(f, r)) {
            lines.push_back(r);
        }
        return lines;
    }

}