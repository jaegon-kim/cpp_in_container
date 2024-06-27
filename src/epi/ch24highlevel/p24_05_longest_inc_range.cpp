#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p24_05 {

    static inline size_t len(size_t s, size_t e) {
        return e - s;
    }

    pair<size_t, size_t> longest_inc_range(const vector<int> & v) {
        size_t max_s = 0, max_e = 0;
        size_t c_s = 0, c_e = 0;

        size_t i = 1;
        for(; i < v.size(); i++) {
            if (v[i - 1] < v[i]) {
                c_e = i;
            } else {
                if (len(max_s, max_e) < len(c_s, c_e)) {
                    max_s = c_s, max_e = c_e;
                }
                c_s = i, c_e = i;
            }
        }

        if (len(max_s, max_e) < len(c_s, c_e)) {
            max_s = c_s, max_e = c_e;
        }

        return make_pair(max_s, max_e);
    }


    void test(const vector<int> & v) {

        auto r = longest_inc_range(v);
        dump_vec_with_idx(v, true);        
        cout << r.first << ", " << r.second << endl;
    }
}

void test_p24_05_longest_inc_range() {
    PRINT_FUNC_NAME;
    p24_05::test(vector<int> {2, 11, 3, 5, 13, 7, 19, 17, 23});
    p24_05::test(vector<int> {2, 11, 3, 5, 13, 7, 19, 17, 23, 24, 25});
}