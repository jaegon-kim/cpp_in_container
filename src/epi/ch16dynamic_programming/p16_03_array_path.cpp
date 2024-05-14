#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;

namespace p16_03 {

    size_t array_path(size_t i, size_t j, size_t len_i, size_t len_j, vector<vector<size_t>> & m) {
        if (i >= len_i || j >= len_j) {
           return 0;
        }

        if (m[i][j]) {
            return m[i][j];
        }

        m[i][j] = array_path(i + 1, j, len_i, len_j, m) + array_path(i, j + 1, len_i, len_j, m); 

        return m[i][j];
    }

    void test(size_t len_i, size_t len_j) {
        vector<vector<size_t>> m(len_i, vector<size_t>(len_j, 0));
        m[len_i - 1][len_j - 1] = 1;

        size_t r = array_path(0, 0, len_i, len_j, m);

        //for (auto v: m) {
        //    dump_vec(v, true);
        //}
        cout << "Number of array path from (0, 0)->(" << (len_i - 1) << ", " << (len_j - 1) << "): " << r << endl; 
    }
}

void test_p16_03_array_path() {
    PRINT_FUNC_NAME;
    p16_03::test(2, 2);
    p16_03::test(2, 3);
    p16_03::test(3, 3);
    p16_03::test(5, 5);
}