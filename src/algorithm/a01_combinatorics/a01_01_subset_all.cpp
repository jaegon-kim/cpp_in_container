#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;

// 1..n 으로 구성된 집합에서 모든 부분 집합 구하기 (순서가 다르게 배치되어도 같은 부분 집합이다)

namespace a01_01 {

    int subset(int c, int k, vector<int> & s_v, vector<int> & s_s_v) {
        if (!k) {
            return 0;
        }
        int cnt = 0;
        for (int i = c; i < (int) s_v.size(); i++) {
            s_s_v.push_back(s_v[i]);
            cnt += subset(i + 1, k - 1, s_v, s_s_v);
            cnt++;
            dump_vec(s_s_v, true);
            s_s_v.pop_back();
        }
        return cnt;
    }

    void test(int n) {
        vector<int> s_v;
        for (int i = 1; i <= n; i++) {
            s_v.push_back(i);
        }
        vector<int> s_s_v;
        int r = subset(0, n, s_v, s_s_v);
        cout << "number of subset: " << r << endl;
    }
}

void test_a01_01_subset_all() {
    PRINT_FUNC_NAME;
    a01_01::test(1);
    a01_01::test(2);
    a01_01::test(3);
    a01_01::test(4);
}
