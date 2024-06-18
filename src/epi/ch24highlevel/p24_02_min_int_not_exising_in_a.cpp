#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p24_02 {


    int min_positive_int_nlogn(const vector<int> & v) {
        auto cmp = [](int a, int b) { return a < b; };
        set<int, decltype(cmp)> s(cmp);
        for (auto e: v) {
            s.emplace(e);
        }

        int min_p_int = 1;
        for (auto e: s) {
            if (e <= 0) {
                continue;
            }
            if (e == min_p_int) {
                min_p_int++;
            }
        }
        return min_p_int;
    }

    int min_positive_int_n(const vector<int> & v) {
        unordered_set<int> s;
        for (auto e: v) {
            s.emplace(e);
        }

        for (int i = 1; i <= 0x7fffffff; i++) {
            if (s.find(i) == s.end()) {
                return i;
            }
        }
        return -1;
    }

    void test(const vector<int> & v) {
        int r_nlogn = min_positive_int_nlogn(v);
        int r_n = min_positive_int_n(v);
        cout << r_nlogn << ", " << r_n << endl;

    }
}

void test_p24_02_min_int_not_exising_in_a() {
    PRINT_FUNC_NAME;
    p24_02::test(vector<int> {3, 5, 4, -1, 5, 1, -1});
    p24_02::test(vector<int> {3, 5, 4, -1, 5, 1, -1, 2});
    p24_02::test(vector<int> {6, 3, 12, 5, 7, 4, 9, -1, 5, 1, -1, 2, 8, 11});

    int v = 0x7fffffff;
    cout << v << endl;
    cout << v + 1 << endl;

}