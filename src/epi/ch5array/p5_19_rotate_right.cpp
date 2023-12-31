#include <iostream>
#include <vector>

#include "utility/dump.hpp"

using namespace std;

namespace p5_19 {

    struct pos {
        int x;
        int y;
    };

    void dump(const vector<vector<int>> & s) {
        int y_len = s.size();
        for (int i = 0; i < y_len; i++) {
            int x_len = s[i].size();
            for (int j = 0; j < x_len; j++) {
                //cout << s[i][j] << ", ";
                printf("%2d, ", s[i][j]);
            }
            cout << endl;
        }
    }

    void rotate_right(const vector<vector<int>> & s, pos p, int len, vector<vector<int>> & t) {

        if (len == 1) {
            t[p.y][p.x] = s[p.y][p.x];
        }

        for (int i = 0; i < len; i++) {
            t[p.y + i][p.x  + len] = s[p.y][p.x + i];
            t[p.y + len][p.x + len - i] = s[p.y + i][p.x + len];
            t[p.y + len - i][p.x] = s[p.y + len][p.x + len - i];
            t[p.y][p.x + i] = s[p.y + len - i][p.x];
        }

        if ((len - 2) < 0) {
            return;
        } else {
            rotate_right(s, {p.y + 1, p.x + 1}, len - 2, t);
        }

    }

    void test(const vector<vector<int>> & s) {
        cout<< "before: " << endl;
        dump(s);
        vector<vector<int>> t = s;
        rotate_right(s, {0, 0}, s.size() - 1, t);
        cout << endl;
        cout<< "after: " << endl;
        dump(t);
    }
}

void test_p5_19_rotate_right() {
    PRINT_FUNC_NAME;

    vector<vector<int>> s_ {
        {1}
    };
    p5_19::test(s_);

    vector<vector<int>> s0 {
        {1, 2},
        {3, 4},
    };
    p5_19::test(s0);

    vector<vector<int>> s1 {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    p5_19::test(s1);

    vector<vector<int>> s2 {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    p5_19::test(s2);

    vector<vector<int>> s3{
        {  1,  2,  3,  4,  5},
        {  6,  7,  8,  9, 10},
        { 11, 12, 13, 14, 15},
        { 16, 17, 18, 19, 20},
        { 21, 22, 23, 24, 25},
    };
    p5_19::test(s3);
}