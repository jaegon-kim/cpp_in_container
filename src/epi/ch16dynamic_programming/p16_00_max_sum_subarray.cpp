#include <iostream>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p16_00_1 {

    pair<size_t, size_t> max_sum_subarray(const vector<int> & v) {
        pair<size_t, size_t> max_idx;
        int max_sum = 0;

        for (size_t i = 0; i < v.size(); i++) {
            int sum = 0;
            for(size_t j = i; j < v.size(); j++) {
                sum += v[j];
                if (sum > max_sum) {
                    max_idx = make_pair(i, j);
                    max_sum = sum;
                }
            }
        }
        return max_idx;
    }

    void test(const vector<int> & v) {
        auto p = max_sum_subarray(v);
        cout << p.first << ", " << p.second << endl;
    }
}

void test_p16_00_max_sum_subarray() {
    PRINT_FUNC_NAME;
    p16_00_1::test(vector<int> {904, 40, 523, 12, -335, -385, -124, 481, -31});
}