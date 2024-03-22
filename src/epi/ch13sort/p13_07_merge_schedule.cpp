#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p13_07 {

    bool compare(const pair<int, int> & a, const pair<int, int> & b) {
        return a.first < b.first;
    }

    vector<pair<int, int>> merge(vector<pair<int, int>> v, pair<int, int> n) {
        vector<pair<int, int>> m;

        v.push_back(n);
        sort(v.begin(), v.end(), compare);
        dump_vec_of_pair(v, true);

        pair<int, int> c = v[0];
        for (size_t i = 1; i < v.size(); i++) {
            if (c.second < v[i].first) {
                m.push_back(c);
                c = v[i];                
            } else {
                if (c.second < v[i].second) {
                    c.second = v[i].second;
                } else {
                    // do nothing
                }
            }
            //dump_vec_of_pair(m, true);
        }
        m.push_back(c);
        return m;
    }

    void test(const vector<pair<int, int>> & v, const pair<int, int> & n) {
        auto m = merge(v, n);
        dump_vec_of_pair(m, false);
        cout << ",   '{" << n.first << ", " << n.second << "}' added" << endl; 
    }
}

void test_p13_07_merge_schedule() {
    PRINT_FUNC_NAME;
    p13_07::test(
        vector<pair<int, int>> {{-4, -1}, {0, 2}, {3, 6}, {7, 9}, {11, 12}, {14, 17}},
        pair<int, int> {1, 8}
    );


    p13_07::test(
        vector<pair<int, int>> {{-4, -1}, {0, 2}, {3, 6}, {7, 9}, {11, 12}, {14, 17}},
        pair<int, int> {-1, 4}
    );

    p13_07::test(
        vector<pair<int, int>> {{-4, -1}, {0, 2}, {3, 6}, {7, 9}, {11, 12}, {14, 17}},
        pair<int, int> {-1, 13}
    );

    p13_07::test(
        vector<pair<int, int>> {{-4, -1}, {0, 2}, {3, 6}, {7, 9}, {11, 12}, {14, 17}},
        pair<int, int> {0, 0}
    );

    p13_07::test(
        vector<pair<int, int>> {{-4, -1}, {0, 2}, {3, 6}, {7, 9}, {11, 12}, {14, 17}},
        pair<int, int> {-1, 15}
    );


}
