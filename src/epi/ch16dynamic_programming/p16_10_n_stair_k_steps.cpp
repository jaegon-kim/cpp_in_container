#include <iostream>
#include "utility/dump.hpp"
using namespace std;

namespace p16_10 {

    int step(const int c, const int n, const int k, vector<int> & cache) {

        if (c == n) {
            return 1;
        }

        if (cache[c]) {
            return cache[c];
        }

        for (int i = 1; i <= k; i++) {
            if ((c + i) > n) {
                continue;
            }
            cache[c] += step(c + i, n, k, cache);
        }
        return cache[c];
    }

    void test(int n, int k) {
        vector<int> cache(n, 0);
        int r = step(0, n, k, cache);
        cout << r << endl;
        dump_vec(cache, true);
    }
}

void test_p16_10_n_stair_k_steps() {
    PRINT_FUNC_NAME;
    p16_10::test(4, 2);
}