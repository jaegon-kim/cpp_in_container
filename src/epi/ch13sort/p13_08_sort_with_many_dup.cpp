#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p13_08 {

    bool compare(const pair<int, vector<string>> & a, const pair<int, vector<string>> & b) {
        return a.first < b.first;
    }

    vector<pair<string, int>> sort(const vector<pair<string, int>> & v) {
        unordered_map<int, vector<string>> map;

        for(const auto & p: v) {
            if (map.find(p.second) == map.end()) {
                map.emplace(p.second, vector<string> {p.first});
            } else {
                map[p.second].push_back(p.first);
            }
        }

        vector<pair<int, vector<string>>> s_m;
        for(const auto & p: map) {
            s_m.push_back(p);
        }
        sort(s_m.begin(), s_m.end(), compare);

        vector<pair<string, int>> s_v;
        for (const auto & p: s_m) {
            //cout << p.first << ", ";
            //dump_vec(p.second, true);
            for(const auto & e: p.second) {
                s_v.push_back(make_pair(e, p.first));
            }
        }
        return s_v;
    }

    void test(const vector<pair<string, int>> & v) {
        auto r = sort(v);
        dump_vec_of_pair(r, true);
    }
}

void test_p13_08_sort_with_many_dup() {
    PRINT_FUNC_NAME;
    p13_08::test(vector<pair<string, int>> {
        {"Greg", 14},
        {"John", 12},
        {"Andy", 11},
        {"Jim", 13},
        {"Phil", 12},
        {"Bob", 13},
        {"Chip", 13},
        {"Tim", 14}
    });
}