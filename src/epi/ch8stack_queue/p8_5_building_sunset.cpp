#include <iostream>
#include <vector>
#include <list>
#include "utility/dump.hpp"

using namespace std;

namespace p8_5 {

    vector<int> l2r(const vector<int> & v) {
        int max_h = 0;
        size_t len = v.size();
        vector<int> sb;
        for (size_t i = 0; i < len; i++) {
            if (v[i] > max_h) {
                max_h = v[i];
                sb.emplace_back(v[i]);
            }
        }
        return sb;
    }    

    void pop_less(list <int> & l, int v) {
        size_t len = l.size();
        for (size_t i = 0; i < len; i++) {
            if (l.front() <= v) {
                l.pop_front();
            } else {
                break;
            }
        }
    }

    vector<int> r2l(const vector<int> & v) {
        int v_len = v.size();
        list<int> l;

        for (int i = v_len; i >= 0; i--) {
            if (v[i] > l.front()) {
                pop_less(l, v[i]);
            }
            l.push_front(v[i]);
        }

        vector<int> sb;
        size_t l_len = l.size();
        for (size_t i = 0; i < l_len; i++) {
            sb.emplace_back(l.front());
            l.pop_front();
        }

        return sb;
    }    

    void test(const vector<int> & v) {
        vector<int> sb_l2r = l2r(v);
        dump_vec(sb_l2r, false);
        vector<int> sb_r2l = r2l(v);
        dump_vec(sb_l2r, true);
    }
}

void test_p8_5_building_suset() {
    PRINT_FUNC_NAME;

    p8_5::test(vector<int> {1, 2, 5, 3, 4, 7, 6, 1, 10});
    p8_5::test(vector<int> {10, 2, 5, 3, 4, 7, 6, 1, 11});
    p8_5::test(vector<int> {11, 2, 5, 3, 4, 7, 6, 1, 11});

}

