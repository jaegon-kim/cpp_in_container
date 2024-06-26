#include <iostream>
#include <vector>
#include <limits>
#include "utility/dump.hpp"
using namespace std;

namespace p25_04 {

    int max_multiple_except_1(const vector<int> & v) {
        size_t min_positive_idx = numeric_limits<size_t>::infinity();
        size_t max_negative_idx = numeric_limits<size_t>::infinity();
        size_t zero_idx = numeric_limits<size_t>::infinity();
        size_t zero_cnt = 0;
        size_t negative_cnt = 0;

        for (size_t i = 0; i < v.size(); i++) {
            if (!v[i]) {
                zero_idx = i;
                zero_cnt++;
            } else if (v[i] < 0) {
                negative_cnt++;
                if (max_negative_idx == numeric_limits<size_t>::infinity()) {
                    max_negative_idx = i;
                } else if (v[i] > v[max_negative_idx]) {
                    max_negative_idx = i;
                }
            } else {
                if (min_positive_idx == numeric_limits<size_t>::infinity()) {
                    min_positive_idx = i;
                } else if (v[i] < v[min_positive_idx]) {
                    min_positive_idx = i;
                }
            }
        }

        size_t exclude_idx;

        if (zero_cnt == 1) {
            if (negative_cnt % 2) {
                return 0;
            }
            exclude_idx = zero_idx;
        } else if (zero_cnt >= 2) {
            return 0;
        } else if (negative_cnt % 2) {
            exclude_idx = max_negative_idx;
        } else {
            exclude_idx = min_positive_idx;
        }
        cout << " exclude idx: " << exclude_idx << "(" << v[exclude_idx] << ") {";

        int max = 1;
        for (size_t i = 0; i < v.size(); i++) {
            if ( i == exclude_idx) {
                continue;
            }
            cout << v[i] << ", ";
            max *= v[i];
        }
        cout << "} ";

        return max;
    }

    void test(const vector<int> & v) {
        cout << endl;
        dump_vec(v, true);
        int max = max_multiple_except_1(v);
        cout << "max: " <<  max << endl;
    }
}

void test_p25_04_max_multiple_except_1() {
    PRINT_FUNC_NAME;
    p25_04::test(vector<int> {3, 2, 5, 4});
    p25_04::test(vector<int> {3, 2, -1, 4});
    p25_04::test(vector<int> {3, 2, -1, 4, -1, 6});
    p25_04::test(vector<int> {3, 2, -1, 4, -2, 6});
    p25_04::test(vector<int> {3, 2, -1, 4, -2, 6, -3});
    p25_04::test(vector<int> {3, 2, -1, 4, -2, 6, -3, -4});
    p25_04::test(vector<int> {3, 2, -1, 4, -2, 6, -3, 0});
    p25_04::test(vector<int> {3, 2, 0, -1, 4, -2, 6, -3, 0});

}