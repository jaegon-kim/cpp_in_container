#include <iostream>
#include "utility/dump.hpp"
#include "vector"

using namespace std;

namespace p11_6 {

    bool search(const vector<vector<int>> & mat, int v) {
        int raw_size = mat.size();
        int col_size = mat[0].size();

        if (mat[0][0] > v) {
            return false;
        }

        int j = 0;
        bool inc = true;
        for (int i = 0; i < raw_size; ) {
            while(true) {
                //cout << "(" << i << ", " << j << ") ";
                if (mat[i][j] == v) {
                    return true;
                }

                if (inc) { // check increasing direction
                    //cout << "->";
                    if ((j + 1) >= col_size) {
                        i++;
                        inc = false;
                        break; 
                    }

                    if (mat[i][j + 1] > v) {
                        if ((i + 1) >= raw_size) {
                            return false;
                        }

                        if (mat[i + 1][j] > v) {
                            inc = false;
                        } else {
                            inc = true;
                        }

                        i++;
                        break;
                    }

                    j++;
                } else { // check decreasing direction
                    //cout << "<-";
                    if ((j - 1) < 0) {
                        i++;
                        inc = true;
                        break;
                    }

                    if (mat[i][j - 1] < v) {
                        if ((i + 1) >= raw_size) {
                            return false;
                        }

                        if (mat[i + 1][j] > v) {
                            inc = false;
                        } else {
                            inc = true;
                        }
                        
                        i++;
                        break;
                    }

                    j--;
                }
            }
        }
        //cout << endl;

        return false;
    }

    void test(const vector<vector<int>> & mat, int v) {
        bool r = search(mat, v);
        cout << "finding " << v << ", result: " << r << endl;
    }
}

void test_p11_6_search_sorted_matrix() {
    PRINT_FUNC_NAME;

    ///*
    auto mat = vector<vector<int>> {
        vector<int> {-1,  2,  4,  4,  6},
        vector<int> { 1,  5,  5,  9, 21},
        vector<int> { 3,  6,  6,  9, 22},
        vector<int> { 3,  6,  8, 10, 24},
        vector<int> { 6,  8,  9, 12, 25},
        vector<int> { 8, 10, 12, 13, 40}
    };
    //*/
    /*
    auto mat = vector<vector<int>> {
        vector<int> {-1,  2,  4,  4,  6},
        vector<int> { 1,  5,  5,  9, 21},
        vector<int> { 3,  7,  8,  9, 22},
        vector<int> { 3,  6,  8, 10, 24},
        vector<int> { 6,  8,  9, 12, 25},
        vector<int> { 8, 10, 12, 13, 40}
    };
    */

    cout << mat[0][0] << endl;
    ///*
    for (size_t i = 0; i < mat.size(); i++) {
        for(size_t j = 0; j < mat[0].size(); j++) {
             p11_6::test(mat, mat[i][j]);
        }
    }
    //*/
    p11_6::test(mat, 7);
    p11_6::test(mat, 14);

}
