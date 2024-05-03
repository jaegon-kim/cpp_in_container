#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include "utility/dump.hpp"

using namespace std;

namespace p15_10 {


    list<int> build_3_3(size_t r, size_t c, vector<vector<int>> & v, 
                    vector<unordered_set<int>> & r_set_vec,  vector<unordered_set<int>> & c_set_vec) {

        unordered_set<int> s;
        for(int i = 1 ; i <= 9; i++) {
            s.emplace(i);
        }

        for(size_t i = r; i < (r + 3); i++) {
            for(size_t j = c; j < (c + 3); j++ ) {
                if (v[i][j]) {
                    s.erase(v[i][j]);
                    r_set_vec[i].erase(v[i][j]);
                    c_set_vec[j].erase(v[i][j]);
                }
            }
        }

        list<int> l;
        for(auto e: s) {
            l.push_back(e);
        }
        return l;
    }

    bool sudoku(size_t r, size_t c, vector<vector<int>> & v,
                    vector<unordered_set<int>> & r_set_vec,  vector<unordered_set<int>> & c_set_vec,
                    vector<vector<list<int>>> & v_v_l_3b3) {
        if (c >= 9) {
            //succeeded to allocate all numbers
            return true;
        }

        if (v[r][c]) { // number is already allocated
            if (r < 8) {
                return sudoku(r + 1, c, v, r_set_vec, c_set_vec, v_v_l_3b3);
            } else {
                return sudoku(0, c + 1, v, r_set_vec, c_set_vec, v_v_l_3b3);
            }
        }

        list<int> & l_3b3 = v_v_l_3b3[r/3][c/3];
        if (!l_3b3.size()) {
            return false;
        }

        size_t len = l_3b3.size();
        for (size_t i = 0 ; i < len; i++) {

            int num = l_3b3.front();
            l_3b3.pop_front();

            if (r_set_vec[r].find(num) == r_set_vec[r].end()) {
                l_3b3.push_back(num);
                continue;
            }

            if (c_set_vec[c].find(num) == c_set_vec[c].end()) {
                l_3b3.push_back(num);
                continue;
            }

            r_set_vec[r].erase(num);
            c_set_vec[c].erase(num);
            v[r][c] = num;

            if (r < 8) {
                if(sudoku(r + 1, c, v, r_set_vec, c_set_vec, v_v_l_3b3)) {
                    return true;
                }
            } else {
                if(sudoku(0, c + 1, v, r_set_vec, c_set_vec, v_v_l_3b3)) {
                    return true;
                }
            }
            r_set_vec[r].emplace(num);
            c_set_vec[c].emplace(num);
            v[r][c] = 0;
            l_3b3.push_back(num);
        }
        return false;
    }


    void test(vector<vector<int>> & v) {

        vector<unordered_set<int>> r_set_vec;
        for(size_t r = 0; r < 9; r++) {
            unordered_set<int> r_set;
            for(int c = 1; c <= 9; c++) {
                r_set.emplace(c);
            }
            r_set_vec.push_back(r_set);
        }

        vector<unordered_set<int>> c_set_vec;
        for(size_t c = 0; c < 9; c++) {
            unordered_set<int> c_set;
            for(int r = 1; r <= 9; r++) {
                c_set.emplace(r);
            }
            c_set_vec.push_back(c_set);
        }

        vector<vector<list<int>>> v_v_l_3b3;
        for (size_t r = 0; r < 3; r++) {
            vector<list<int>> v_l;
            for (size_t c = 0; c < 3; c++) {
                list<int> l = build_3_3(r * 3, c * 3, v, r_set_vec, c_set_vec);
                //dump_list(l, true);
                v_l.push_back(l);
            }
            v_v_l_3b3.push_back(v_l);
        }               
        auto r = sudoku(0, 0, v, r_set_vec, c_set_vec, v_v_l_3b3);
        if (r) {
            cout << "found" << endl;
            dump_vec_of_vec(v);
        } else {
            cout << "failed to find" << endl;
        }
    }
}

void test_p15_10_sudoku() {
    PRINT_FUNC_NAME;
    /* // completed sudoku
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
    */
    vector<vector<int>> v {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},
    };

    p15_10::test(v);
}
