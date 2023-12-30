#include <iostream>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p5_17 {

    struct range {
        int start;
        int end;
    };

    bool is_dup(const vector<vector<int>> & s, range row, range col) {
        vector<bool> c((row.end - row.start + 1) * (col.end - col.start + 1), false);
        //cout <<  __func__ << "c size: " << c.size() << endl;

        for (int i = row.start; i <= row.end; i++) {
            for (int j = col.start; j <= col.end; j++) {
                if (c[s[i][j]]) {
                    return true;
                }                
                c[s[i][j]] = true;
            }
        }
        return false;
    }

    bool is_valid(const vector<vector<int>> & s, int row_size, int col_size) {

        for (int i = 0; i < row_size; i++) {
            if(is_dup(s, range {i, i}, range {0, col_size - 1})) {
                return false;
            }
        }

        for (int i = 0; i < col_size; i++) {
            if(is_dup(s, range {0, row_size - 1}, range {i, i})) {
                return false;
            }
        }

        for (int i = 0; i < row_size; i += 3) {
            for (int j = 0; j < col_size; j += 3) {
                if (is_dup(s, range {i, i + 2}, range {j, j + 2})) {
                    return false;
                }
            }
        }

        return true;
    }

    void test(const vector<vector<int>> & s) {

        bool rslt = is_valid(s, s.size(), s[0].size());
        cout << (rslt? "valid" : "invalid") << endl;
    }

}

void test_p5_17_validate_sudoku_sol() {
    PRINT_FUNC_NAME;
    vector<vector<int>> v {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9},
    };
    p5_17::test(v);
    v[0][0] = 1;
    p5_17::test(v);

}