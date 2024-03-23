#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p13_12 {

    bool compare(int a, int b) {
        return a < b;
    }

    int salary_cap(vector<int> v, int tot_cap) {
        sort(v.begin(), v.end(), compare);
        dump_vec(v, true);

        for(size_t i = 0; i < v.size(); i++) {

            int cap = tot_cap / (v.size() - i);
            if (v[i] > cap) {
                return cap;
            }
            tot_cap -= v[i];
        }
     
        return 0;
    }

    void test(const vector<int> & v, int tot_cap) {
        cout << salary_cap(v, tot_cap) << endl;
    }
}

void test_p13_12_salary_cap() {
    PRINT_FUNC_NAME;
    p13_12::test(vector<int> {90, 30, 100, 40, 20}, 210);
}