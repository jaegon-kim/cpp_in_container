#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p15_05 {

    void power_set(const vector<int> & v, vector<vector<int>> & ps_v) {
        ps_v.push_back(vector<int>());
        for (auto i = v.begin(); i != v.end(); i++) {
            auto j = i + 1;
            for (; j != v.end(); j++) {
                ps_v.push_back(vector<int> (i, j));
            }
            vector<int> e(i, j);
            ps_v.push_back(vector<int> (i, j));
        }
    }

    bool compare(const vector<int> & a, const vector<int> & b) {
        return a.size() < b.size();
    }

    void test(const vector<int> & input_v) {
        vector<int> v = input_v;
        vector<vector<int>> ps_v;
        power_set(v, ps_v);
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
}