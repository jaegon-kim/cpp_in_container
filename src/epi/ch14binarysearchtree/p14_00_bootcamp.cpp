#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p14_00 {
    void test() {
        vector<int> v {1, 2, 3, 4, 4, 5};
        set<int> s;
        for(const auto & e: v) {
            s.emplace(e);
        }
        dump_set(s, true);

        auto f = s.find(3);
        cout << *f << endl;

        f = s.find(7);
        cout << *f << endl;


        vector<pair<string, int>> v2 {{"a", 1}, {"b", 2}, {"c", 3}, {"c", 4}, {"d", 5}};
        map<string, int> m;
        for(const auto & e: v2) {
            m.emplace(e.first, e.second);
        }
        dump_map(m, true);


    }
}

void test_p14_00_bootcamp() {
    PRINT_FUNC_NAME;
    p14_00::test();
}