#include <iostream>
#include "utility/dump.hpp"
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

namespace p13_03 {

    bool compare(int a, int b) {
        return a > b;
    }

    int h_idx(vector<int> v) {
        sort(v.begin(), v.end(), compare);
        dump_vec(v, true);

        for(int i = 0; i < (int) v.size(); i++) {
            if (i >= v[i]) {
                return i;
            }
        }
        return -1;
    }

    void test(const vector<int> & t) {
        vector<int> v = t;
        size_t h = h_idx(v);
        cout << h << endl; 
    }

    vector<int> gen_rand(size_t s, int max) {
        vector<int> v;
        for(size_t i = 0; i < s; i++) {
            v.push_back(rand() % max);
        }
        return v;
    }
}

void test_p13_03_h_index() {
    PRINT_FUNC_NAME;
    p13_03::test(vector<int> {4, 1, 3, 0, 2});

   srand((int)time(NULL));
    for(size_t i = 0 ; i < 10; i++) {
        vector<int> r = p13_03::gen_rand(10, 10);
        p13_03::test(r);
    }
}