#include <iostream>
#include <list>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p16_04 {

    int subset(int c, int k, vector<int> & v, vector<int> & subset_v) {
        if (!k) {
            dump_vec(subset_v, true);
            return 1;
        }

        int cnt = 0;
        for (int i = c + 1; i < (int) v.size(); i++) {
            subset_v.push_back(v[i]);
            cnt += subset(i, k - 1, v, subset_v);
            subset_v.pop_back();
        }

        return cnt;
    }

    void test(int n, int k) {
        vector<int> v;
        for (int i = 1; i <= n; i++) {
            v.push_back(i);
        }
        vector<int> subset_v;
        int r = subset(-1, k, v, subset_v);
        cout << "n: " << n << ", k: " << k << ", # of subset: " <<  r << endl;
    }
}

void test_p16_04_binomial_coefficient() {
    PRINT_FUNC_NAME;
    p16_04::test(4, 2);
    p16_04::test(4, 3);
    p16_04::test(5, 2);
    p16_04::test(5, 3);
}