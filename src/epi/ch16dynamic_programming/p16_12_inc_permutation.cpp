#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;

namespace p16_12 {

    vector<int> longest_inc_permutation(const vector<int> & v, const vector<size_t> & cache, size_t s) {

        vector<int> p;
        p.push_back(v[s]);
        s = cache[s];
        while(s) {
            p.push_back(v[s]);
            s = cache[s];
        }
        return p;
    }

    size_t permutation(const vector<int> & v, size_t c, vector<size_t> & cache) {
        if (c == (v.size() - 1)) {
            return 1;
        }

        size_t longest_i = 0, longest_len = 0;
        for (size_t i = c + 1; i < v.size(); i++) {
            if (v[i] < v[c]) {
                continue;
            }
            size_t len = permutation(v, i, cache) + 1;
            if (len > longest_len) {
                longest_len = len;
                longest_i = i;
            }
        }

        cache[c] = longest_i;
        return longest_len;
    }

    void test(const vector<int> & v) {
        vector<size_t> cache(v.size(), 0);
        size_t r = permutation(v, 0, cache);
        cout << r << endl;
        cout << "cache: ";
        dump_vec(cache, true);
        auto p = longest_inc_permutation(v, cache, 0);
        cout << "longest increasing permutation: ";
        dump_vec(p, true);
    }
}

void test_p16_12_inc_permutation() {
    p16_12::test(vector<int> {0, 8, 4, 12, 2, 10, 6, 14, 1, 9});
}