#include <iostream>
#include <vector>
#include <set>
#include "utility/dump.hpp"
using namespace std;
namespace p24_06 {

    void dump(const vector<vector<bool>> & v) {
        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = 0; j < v[i].size(); j++) {
                cout << v[i][j] << ", ";
            }
            cout << endl;
        }
    }

    void update(vector<vector<bool>> & v) {
        set<size_t> row_s;
        set<size_t> col_s;

        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = 0; j < v[i].size(); j++) {
                if (!v[i][j]) {
                    row_s.emplace(i);
                    col_s.emplace(j);
                }
            }
        }

        //cout << "row: ";
        //dump_set(row_s, true);
        //cout << "col: ";
        //dump_set(col_s, true);
        for(auto e: row_s) {
            for(size_t i = 0; i < v[e].size(); i++) {
                v[e][i] = 0;
            }
        }

        for(auto e: col_s) {
            for(size_t i = 0; i < v.size(); i++) {
                v[i][e] = 0;
            }
        }
    }

    void test(vector<vector<bool>> v) {
        dump(v);
        update(v);
        cout << endl;
        dump(v);
    }

}

void test_p24_07_update_rook_attack_pos() {
    PRINT_FUNC_NAME;
    const vector<vector<bool>> v = 
    {
        {1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
    };

    p24_06::test(v);
}