#include <iostream>
#include <vector>
#include <list>
#include "utility/dump.hpp"

using namespace std;

namespace p16_08 {

    size_t left_child(size_t current_idx, size_t depth) {
        return current_idx + depth;
    }

    list<int> mincost(const vector<int> & t, size_t c_i, size_t child_depth, int & cost_sum, vector<pair<int, list<int>>> & min_cache) {

        size_t l_c = left_child(c_i, child_depth);
        list<int> p;

        if (l_c >= t.size()) {
            cost_sum = t[c_i];
            p.push_front(c_i);
            return p;
        }

        if (min_cache[c_i].first) {
            cost_sum = min_cache[c_i].first;
            return min_cache[c_i].second;
        }

        int cs_1 = 0, cs_2 = 0;
        list<int> r1 = mincost(t, l_c    , child_depth + 1, cs_1, min_cache);
        list<int> r2 = mincost(t, l_c + 1, child_depth + 1, cs_2, min_cache);
        if (cs_1 < cs_2) {
            cost_sum = cs_1 + t[c_i];
            r1.push_front(c_i);
            min_cache[c_i].first = cost_sum;
            min_cache[c_i].second = r1;
            return r1;
        } else {
            cost_sum = cs_2 + t[c_i];
            r2.push_front(c_i);
            min_cache[c_i].first = cost_sum;
            min_cache[c_i].second = r2;
            return r2;
        }
    }

    void test(const vector<int> & t) {
        int cs = 0; 
        vector<pair<int, list<int>>> min_cache(t.size(), make_pair(0, list<int>()));

        list<int> r = mincost(t, 0, 1, cs, min_cache);
        cout << cs << endl;
        dump_list(r, true);
    }
}

void test_p16_08_number_triangle() {
    PRINT_FUNC_NAME;
    vector<int> t{2, 4, 4, 8, 5, 6, 4, 2, 6, 2, 1, 5, 2, 3, 4};
    p16_08::test(t);
}
