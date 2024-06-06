#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"
using namespace std;

namespace p17_01 {

    bool compare(const int & a, const int & b) {
        return a < b;
    }

    int assign(const vector<int> & v, vector<pair<size_t, size_t>> & a) {
        size_t len = v.size() / 2;
        int max_t = 0;
        for (size_t i = 0; i < len; i++) {
            a.push_back(make_pair(v[i], v[v.size() - 1 - i]));
            int t = v[i] + v[v.size() - 1 - i];
            if (t > max_t) {
                max_t = t;
            }
        }
        return max_t;
    }

    void test(const vector<int> & v) {
        vector<int> v2 = v;
        sort(v2.begin(), v2.end(), compare);
        dump_vec(v2, true);
        vector<pair<size_t, size_t>> a;
        int r = assign(v2, a);
        cout << r << endl;
        dump_vec_of_pair(a, true);
    }
}

void test_p17_01_assign_2_job() {
    PRINT_FUNC_NAME;
    p17_01::test(vector<int> {5, 2, 1, 6, 4, 4});
}