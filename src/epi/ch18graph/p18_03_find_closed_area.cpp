#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p18_03 {


    void bfs(vector<vector<bool>> & map, int r_idx, int c_idx) {
        if ((r_idx < 0) || (r_idx >= (int) map.size()) || 
            (c_idx < 0) || (c_idx >= (int) map[0].size())) {
            return;
        }
        if (!map[r_idx][c_idx]) {
            return;
        }
        map[r_idx][c_idx] = false;
        //cout << __func__ << " r: " << r_idx << ", c:" << c_idx << endl;
        vector<pair<int, int>> dir = {
            {r_idx, c_idx + 1}, {r_idx + 1, c_idx}, {r_idx, c_idx - 1}, {r_idx - 1, c_idx}
        };
        for (const auto & [n_r_idx, n_c_idx]: dir) {
            bfs(map, n_r_idx, n_c_idx);
        }
    }

    void find_closed_area(vector<vector<bool>> & map) {
        //cout << endl;
        //dump_vec_of_vec(map);
        for (int i = 0; i < (int) map.size(); i++) {
            bfs(map, i, 0);
            bfs(map, i, map[0].size() - 1);
        }
        for (size_t i = 1; i < (map.size() - 1); i++) {
            bfs(map, 0, i);
            bfs(map, map.size() - 1, i);
        }
        //cout << endl;
        //dump_vec_of_vec(map);
    }

    void test(vector<vector<bool>> i_map) {
        cout << endl;
        dump_vec_of_vec(i_map);
        vector<vector<bool>> t_map = i_map;
        find_closed_area(t_map);
        for (int i = 0 ; i < (int)i_map.size(); i++) {
            for (int j = 0; j < (int)i_map[0].size(); j++) {
                if (t_map[i][j]) {
                    i_map[i][j] = false;
                }
            }
        }
        cout << endl;
        dump_vec_of_vec(i_map);
    }
}
void test_p18_03_find_closed_area() {
    PRINT_FUNC_NAME;
    p18_03::test({
            {false, false, false, false},
            {true, false, true, false},
            {false, true, true, false},
            {false, false, false, false}
        }
    );

        p18_03::test({
            {false, false, false, false, false},
            {true, false, false, true, false},
            {false, true, true, false, false},
            {false, true, false, false, true},
            {false, true, false, false, false},
        }
    );
}