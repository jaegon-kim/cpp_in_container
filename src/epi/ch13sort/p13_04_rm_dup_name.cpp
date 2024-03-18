#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p13_04 {

    bool compare(const pair<string, string> & p1, const pair<string, string> & p2) {
        return p1.first.compare(p2.first) < 0;
    }

    vector<pair<string, string>> rm_dup_name(vector<pair<string, string>> & v) {
        sort(v.begin(), v.end(), compare);

        vector<pair<string, string>> r;
        r.push_back(v[0]);

        for(size_t i = 1; i < v.size(); i++) {
            if (r.back().first.compare(v[i].first)) {
                r.push_back(v[i]);
            }
        }
        return r;
    }

    void test(const vector<pair<string, string>> & t) {
        vector<pair<string, string>> v = t;
        dump_vec_of_pair(v, true);

        vector<pair<string, string>> r = rm_dup_name(v);
        dump_vec_of_pair(r, true);
    }
}

void test_p13_04_rm_dup_name() {
    PRINT_FUNC_NAME;
    p13_04::test(vector<pair<string, string>> {
        {"Ian", "Botham"}, {"David", "Gower"}, {"Ian", "Bell"}, {"Ian", "Chappell"}
    });
}

