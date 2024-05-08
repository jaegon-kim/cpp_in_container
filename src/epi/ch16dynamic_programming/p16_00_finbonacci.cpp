#include <iostream>
#include "utility/dump.hpp"
#include <unordered_map>

using namespace std;

namespace p16_00 {

    int fibonacci_cache(int n, unordered_map<int, int> & cache) {
        if (n <= 1) {
            return n;
        }
        if (cache.find(n) == cache.end()) {
            cache.emplace(n, fibonacci_cache(n - 1, cache) + fibonacci_cache(n - 2, cache));
        }
        return cache[n];
    }

    int finbonacci_loop(int n) {
        if (n <= 1) {
            return n;
        }
        int n_2 = 0;
        int n_1 = 1;
        int v = 0;
        for (int i = 2; i <= n; i++) {
            v = n_1 + n_2;
            n_2 = n_1;
            n_1 = v;
        }
        return v;
    }

    void test() {
        unordered_map<int, int> cache;
        for(int i = 0 ; i < 10; i++) {
            cout << "finbonacci(" << i << "): ";
            cout <<  fibonacci_cache(i, cache) << ", ";
            cout << finbonacci_loop(i) << endl;
        }
    }
}

void test_p16_00_finbonacci() {
    PRINT_FUNC_NAME;
    p16_00::test();
}