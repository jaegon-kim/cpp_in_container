#include <iostream>
#include <vector>
#include <optional>
#include <unordered_set>

#include "utility/dump.hpp"

using namespace std;

namespace p12_11 {

    optional<vector<int>> collatz_permutation(int n, unordered_set<int> & set) {
        vector<int> vec;

        for(size_t i = 0; i < 1000; i++) {
            vec.push_back(n);
            if (n == 1) {
                for (int v: vec) {
                    set.emplace(v);
                }
                return vec;
            }            
            if ((n % 2) == 0) {
                n = n / 2;
            } else {
                n = n * 3 + 1;
            }
        }

        return nullopt;
    }

    void test(int n) {
        unordered_set<int> set;
        for (int i = 1; i <= n; i++) {
            if (set.find(i) != set.end()) {
                //cout << "pass - " << i << endl;
                continue;
            }
            auto opt = collatz_permutation(i, set);
            if (opt == nullopt) {
                cout << i << " - overflow" << endl;
            } else {
                //cout << "collatz permutation : " << endl;
                //dump_vec(opt.value(), true);
            }
        }
    }

}

void test_p12_11_collatz_conjecture() {
    PRINT_FUNC_NAME;
    p12_11::test(100);
}