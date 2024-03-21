#include <iostream>
#include <algorithm>
#include <vector>

#include "utility/dump.hpp"

using namespace std;

namespace p13_06 {

    bool compare(const pair<int, bool> & a, const pair<int, bool> & b) {
        return a.first < b.first;
    }

    int calendar_max_dup_schedule(vector<pair<int, int>> & i_v) {
        vector<pair<int, bool>> s_v; 
        for (const pair<int, int> & p: i_v) {
            s_v.push_back(make_pair(p.first, true));
            s_v.push_back(make_pair(p.second, false));
        }
        sort(s_v.begin(), s_v.end(), compare);
        dump_vec_of_pair(s_v, true);

        int depth = 0;
        int max_depth = 0;
        for (const pair<int, bool> & p: s_v) {
            if (p.second) {
                depth++;
                if (depth > max_depth) {
                    max_depth = depth;
                }                
            } else {
                depth--;
            }
        }

        return max_depth;
    }

    void test(vector<pair<int, int>> & v) {
        int max_dup = calendar_max_dup_schedule(v);
        cout << max_dup << endl;
    }    
}

void test_p13_06_calendar_max_dup_sch() {
    PRINT_FUNC_NAME;

    auto v = vector<pair<int, int>> {
        {1, 5},
        {6, 10},
        {11, 13},
        {14, 15},
        {2, 7},
        {8, 9},
        {12, 15},
        {4, 5},
        {9, 17}
    };

    p13_06::test(v);
}