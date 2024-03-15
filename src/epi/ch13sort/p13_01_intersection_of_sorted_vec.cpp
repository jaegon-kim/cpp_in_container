#include <iostream>
#include <ctime>
#include <algorithm>

#include "utility/dump.hpp"

using namespace std;

namespace p13_01 {

    vector<int> intersection(const vector<int> & va, const vector<int> & vb) {

        size_t idx_a = 0;
        size_t idx_b = 0;
        vector<int> vi;

        while(idx_a < va.size() && idx_b < vb.size()) {
            if (va[idx_a] == vb[idx_b]) {
                if (!vi.size() || vi.back() != va[idx_a]) {
                    vi.push_back(va[idx_a]);
                }
                idx_a++;
                idx_b++;            
            } else if (va[idx_a] < vb[idx_b]) {
                idx_a++;
            } else {
                idx_b++;
            }
        }
        return vi;
    }

    void test(const vector<int> & va, const vector<int> & vb) {
        dump_vec(va, false);
        dump_vec(vb, false);
        vector<int> vi = intersection(va, vb);
        dump_vec(vi, true);
    }

    vector<int> rand_vec(size_t s) {
        vector<int> v;
        for(size_t i = 0 ; i < s; i++) {
            v.push_back(rand() % s);
        }
        return v;
    }

    bool compare(int a, int b) {
        return a < b;
    }
}

void test_p13_01_intersection_of_sorted_vec() {
    PRINT_FUNC_NAME;   
    p13_01::test(vector<int> {2, 3, 3, 5, 5, 6, 7, 7, 8, 12}, vector<int> {5, 5, 6, 8, 8, 9, 10, 10});

    srand((int)time(NULL));

    size_t s = 7;

    for(size_t i = 0; i < 10; i++) {
        vector<int> va = p13_01::rand_vec(rand() % s + 3);
        vector<int> vb = p13_01::rand_vec(rand() % s + 3);
        sort(va.begin(), va.end(), p13_01::compare);
        sort(vb.begin(), vb.end(), p13_01::compare);
        p13_01::test(va, vb);
    }

}
