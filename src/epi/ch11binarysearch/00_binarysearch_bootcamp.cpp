#include <iostream>

#include "utility/dump.hpp"

using namespace std;

namespace p11_00 {

    // v is a sorted vector
    int bsearch(const vector<int> & v, int k) {
        int s = 0;
        int e = v.size() - 1;

        while(s <= e) {
            size_t m = (s + e) / 2;
            if (v[m] == k) {
                return m;
            } else if (k < v[m]) {
                e = m - 1;
            } else {
                s = m + 1;
            }
        }

        return -1;
    }

    void test(const vector<int> & v, int k) {
        int r = bsearch(v, k);
        cout << r << endl;
    }
}


void test_00_binarysearch_bootcamp() {
    PRINT_FUNC_NAME;
    const vector<int> v {-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};
    for (auto e : v) {
        p11_00::test(v , e);
    }
    p11_00::test(v , 0);
    p11_00::test(v , 100);

}