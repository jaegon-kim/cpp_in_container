#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std; 

namespace p15_06 {

    void subset_len_k(const vector<int> &v, size_t c, size_t k, vector<int> & p, vector<vector<int>> & ps_v) {
        size_t len_v = v.size();

        if ((p.size() + (len_v - c)) < k) {
            return;
        }

        for (size_t i = c; i < len_v; i++) {
            p.push_back(v[i]);
            if (p.size() == k) {
                ps_v.push_back(p);
                p.pop_back();
                continue;
            }

            subset_len_k(v, i + 1, k, p, ps_v);
            p.pop_back();
        }
    }

    bool compare(const vector<int> & a, const vector<int> & b) {
        return a.size() < b.size();
    }

    void test(const vector<int> & i_v, size_t k) {
        vector<int> v = i_v;
        vector<int> p;
        vector<vector<int>> ps_v;

        subset_len_k(v, 0, k, p, ps_v);
        sort(ps_v.begin(), ps_v.end(), compare);

        cout << "subset len k(" << k << ") of ";
        dump_vec(i_v, true);
        for(auto e: ps_v) {
            dump_vec(e, true);
        }
    }
}

void test_p15_06_subset_len_k() {
    PRINT_FUNC_NAME;
    p15_06::test(vector<int> {0, 1, 2, 3}, 1);
    p15_06::test(vector<int> {0, 1, 2, 3}, 2);
    p15_06::test(vector<int> {0, 1, 2, 3}, 3);
    p15_06::test(vector<int> {0, 1, 2, 3}, 4);
}