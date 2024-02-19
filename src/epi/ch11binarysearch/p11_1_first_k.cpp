#include <iostream>

#include "utility/dump.hpp"

using namespace std;

namespace p11_1 {

    // v is a sorted vector
    int bsearch_first_k(const vector<int> & v, int k) {
        int s = 0;
        int e = v.size() - 1;

        while(s <= e) {
            int m = (s + e) / 2;
            if (v[m] == k) {
                while( (m - 1) >= 0 && v[m - 1] == k) {
                    m--;
                }
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
        int r = bsearch_first_k(v, k);
        cout << r << endl;
    }
}


void test_p11_1_first_k() {
    PRINT_FUNC_NAME;
    const vector<int> v {-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};
    for (auto e : v) {
        p11_1::test(v , e);
    }
    p11_1::test(v , 0);
    p11_1::test(v , 100);

}