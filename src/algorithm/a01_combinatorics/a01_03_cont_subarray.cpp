#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;

namespace a01_03 {

    // 1..n 으로 구성된 연속된 sub array ()

    int cont_subarray(vector<int> a) {
        int cnt = 0;
        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = i; j < a.size(); j++) {
                cnt++;
                vector<int> sub_a(&a[i], &a[j+1]);
                dump_vec(sub_a, true);
            }
        }
        return cnt;
    }

    void test(int n) {
        vector<int> a;
        for (int i = 1; i <= n; i++) {
            a.push_back(i);
        }
        int r = cont_subarray(a);
        cout << "number of continuous sub array: " << r << endl;
    }
}

void test_a01_03_cont_subarray() {
    a01_03::test(1);
    a01_03::test(2);
    a01_03::test(3);
    a01_03::test(4);
}