#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p14_00 {
    void test() {
        vector<int> v {1, 5, 3, 4, 2, 4, 8, 7};
        set<int> s;
        for(const auto & e: v) {
            s.emplace(e);
        }
        dump_set(s, true);

        auto f = s.find(3);
        cout << *f << endl;

        f = s.find(7);
        cout << *f << endl;

        for (auto iter = s.begin(); iter != s.end(); iter++) {
            cout << *iter << ", ";
        }
        cout << endl;

        cout << "begin: " << *s.begin() << endl;
        cout << "end: " << *s.end() << endl;

        s.erase(s.begin());
        dump_set(s, true);

        s.erase(s.begin());
        dump_set(s, true);

        s.erase(s.begin());
        dump_set(s, true);

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