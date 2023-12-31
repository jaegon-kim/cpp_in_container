#include <iostream>
#include <vector>

#include "utility/dump.hpp"

using namespace std;

namespace p5_18 {

    struct pos {
        int x;
        int y;
    };

    void read_spiral_order(const vector<vector<int>> & s, pos p, int len, vector<int> & v) {

        if (len == 0) {
            v.emplace_back(s[p.y][p.x]);
            return;
        }

        for (int i = 0; i < len; i++) {
            v.emplace_back(s[p.y][p.x + i]);
        }

        for (int i = 0; i < len; i++) {
            v.emplace_back(s[p.y + i][p.x + len]);
        }

        for (int i = 0; i < len; i++) {
            v.emplace_back(s[p.y + len][p.x + len - i]);
        }

        for (int i = 0; i < len; i++) {
            v.emplace_back(s[p.y + len -i][p.x]);
        }

        if ((len - 2) < 0) {
            return;

        } else {
            read_spiral_order(s, {p.y + 1, p.x + 1}, len - 2, v);
            return;
        }
    }


    void test(const vector<vector<int>> & s) {
        vector<int> r;
        read_spiral_order(s, pos{0, 0}, s[0].size() - 1, r);

        dump_vec(r, true);
    }
}


void test_p5_18_read_spiral_order() {
    PRINT_FUNC_NAME;

    vector<vector<int>> s_ {
        {1}
    };
    p5_18::test(s_);

    vector<vector<int>> s0 {
        {1, 2},
        {3, 4},
    };
    p5_18::test(s0);

    vector<vector<int>> s1 {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    p5_18::test(s1);

    vector<vector<int>> s2 {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    p5_18::test(s2);

    vector<vector<int>> s3{
        {  1,  2,  3,  4,  5},
        {  6,  7,  8,  9, 10},
        { 11, 12, 13, 14, 15},
        { 16, 17, 18, 19, 20},
        { 21, 22, 23, 24, 25},
    };
    p5_18::test(s3);


}