#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include "utility/dump.hpp"
using namespace std;

//#define PRINT_LINE {cout << __LINE__ << endl;}
#define PRINT_LINE {}


namespace p18_01 {

    struct Loc {
        int r_idx = 0;
        int c_idx = 0;

        unsigned long long key() const {
            return ((unsigned long long) r_idx) << 32 | ((unsigned long long) c_idx);
        }

        bool operator==(const Loc & other) {
            return other.c_idx == c_idx && other.r_idx == r_idx;
        }
    };

    static inline bool range_out(const vector<vector<int>> & map, const Loc & loc) {
        return (loc.r_idx < 0 || loc.r_idx >= (int) map.size() ||
                 loc.c_idx < 0 || loc.c_idx >= (int) map.size());
    }

    list<Loc> maze_search(const vector<vector<int>> & map, Loc cur, Loc end,
                        unordered_set<unsigned long long> & visited) {
        //cout << __func__ << "(" << cur.r_idx << ", " << cur.c_idx << ")" << endl;
        if (range_out(map, cur)) {
            PRINT_LINE;
            return list<Loc>();
        }

        if (map[cur.r_idx][cur.c_idx]) {
            PRINT_LINE;
            return list<Loc>();
        }

        if (visited.find(cur.key()) != visited.end()) {
            // cycle
            PRINT_LINE;
            return list<Loc>();
        }

        if (cur.r_idx == end.r_idx && cur.c_idx == end.c_idx) {
            // found
            list<Loc> path;
            path.push_front(cur);
            PRINT_LINE;
            return path;
        }

        vector<Loc> v {
            {cur.r_idx, cur.c_idx + 1}, {cur.r_idx, cur.c_idx - 1}, {cur.r_idx + 1, cur.c_idx}, {cur.r_idx - 1, cur.c_idx}
        };

        visited.emplace(cur.key());
        for (const Loc & e: v) {
            list<Loc> path = maze_search(map, e, end, visited);
            if (path.size()) {
                PRINT_LINE;
                visited.erase(cur.key());
                path.push_front(cur);
                return path;
            }
        }
        PRINT_LINE;
        visited.erase(cur.key());
        return list<Loc>();
    }

    void dump_loc_list(const list<Loc> & l, bool nl) {
        cout << "{";
        for (const auto & e: l) {
            cout << "(" << e.r_idx << ", " << e.c_idx << "), ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void test(const vector<vector<int>> & map, Loc start, Loc end) {
        unordered_set<unsigned long long> visited;
        list<Loc> p = maze_search(map, start, end, visited);
        dump_loc_list(p, true);
    }
}

void test_p18_01_maze_search() {
    PRINT_FUNC_NAME;
    p18_01::test(
        {
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 0, 1, 1, 0, 1, 1},
            {0, 0, 0, 1, 1, 1, 0, 0, 1, 0},
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 0},
            {1, 0, 1, 1, 0, 0, 0, 1, 1, 1},
            {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
        },
        {9, 0},
        {0, 9}
    );
}