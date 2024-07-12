#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p18_02 {

    void dump_map(const vector<vector<bool>> & map) {
        for (const auto & r : map) {
            cout << "(";
            for (const auto & p : r) {
                cout << p << ", ";
            }
            cout << ")" << endl;
        }
    }

    void flip(vector<vector<bool>> & map, int r, int c) {
        bool color = map[r][c];
        map[r][c] = !color;

        vector<pair<int, int>> nexts = {
            {r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}
        };

        for (const auto & [n_r, n_c]: nexts) {
            if ( (n_r < 0) || (n_r >= map.size()) 
              || (n_c < 0) || (n_c >= map[0].size())
              || map[n_r][n_c] != color) {
                continue;
            }
            flip(map, n_r, n_c);
        }
    }

    void test(vector<vector<bool>> map, int r, int c) {
        dump_map(map);
        flip(map, r, c);
        cout << endl;
        dump_map(map);
        flip(map, 3, 5);
        cout << endl;
        dump_map(map);

    } 
}


void test_p18_02_flip_area() {
    PRINT_FUNC_NAME;
    p18_02::test(
        {
            {true, false, true, false, false, false, true, true, true, true},
            {false, false, true, false, false, true, false, false, true, true},
            {true, true, true, false, false, true, true, false, true, true},
            {false, true, false, true, true, true, true, false, true, false},
            {true, false, true, false, false, false, false, true, false, false},
            {true, false, true, false, false, true, false, true, true, true},
            {false, false, false, false, true, false, true, false, false, true},
            {true, false, true, false, true, false, true, false, false, false},
            {true, false, true, true, false, false, false, true, true, true},
            {false, false, false, false, false, false, false, true, true, false}            
        }
        , 5, 4
    );

}