#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p15_05 {

    void power_set(const vector<int> & v, size_t c, vector<int> & p, vector<vector<int>> & ps_v) {
        size_t v_len = v.size();
        if (c == v_len) {
            return;
        }

        for (size_t i = c; i < v_len; i++) {
            p.push_back(v[i]);
            ps_v.push_back(p);
            power_set(v, i + 1, p, ps_v);
            p.pop_back();
        }
    }

    bool compare(const vector<int> & a, const vector<int> & b) {
        return a.size() < b.size();
    }

    void test(const vector<int> & input_v) {
        vector<int> v = input_v;
        vector<int> p;
        vector<vector<int>> ps_v;
        ps_v.push_back(p);
        power_set(v, 0, p, ps_v);
        sort(ps_v.begin(), ps_v.end(), compare);

        cout << "power set of ";
        dump_vec(v, true);
        cout << "(len:" << ps_v.size() << ") " << endl;
        for (auto e: ps_v) {
            dump_vec(e, true);
        }
    }
}

void test_p15_05_power_set() {
    PRINT_FUNC_NAME;
    p15_05::test(vector<int> {0});
    p15_05::test(vector<int> {0, 1});
    p15_05::test(vector<int> {0, 1, 2});
    p15_05::test(vector<int> {0, 1, 2, 3});

}