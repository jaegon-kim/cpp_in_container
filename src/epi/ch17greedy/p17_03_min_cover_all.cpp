#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"
using namespace std;
namespace p17_03 {

    bool compare(const pair<int, int> & a, const pair<int, int> & b) {
        return a.second < b.second;
    }

    vector<int> min_cover_all(vector<pair<int, int>> v) {
        vector<int> r;

        sort(v.begin(), v.end(), compare);
        dump_vec_of_pair(v, true);

        pair<int, int> c = v[0];
        r.push_back(c.second);

        for (size_t i = 1; i < v.size(); i++) {

            if (v[i].first <= c.second) {
                continue;
            }

            c = v[i];
            r.push_back(c.second);
        }

        return r;
    }

    void test(const vector<pair<int, int>> & v) {
        dump_vec_of_pair(v, true);
        auto r = min_cover_all(v);
        dump_vec(r, true);
    }
}

void test_p17_03_min_cover_all() {
    PRINT_FUNC_NAME;
    //p17_03::test({{0, 3}, {2, 6}, {3, 4}, {6, 9}});
    p17_03::test({{1, 2}, {2, 3}, {3, 4}, {2, 3}, {3, 4}, {4, 5}});

}