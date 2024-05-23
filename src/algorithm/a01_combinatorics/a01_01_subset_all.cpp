#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;

// 1..n 으로 구성된 집합에서 모든 부분 집합 구하기 (순서가 다르게 배치되어도 같은 부분 집합이다)

namespace a01_01 {

    // vector의 시작 인덱스를 조정해서, 원소 i의 포함여부를 선택하는 방법
    int subset_with_start_idx(int c, int k, vector<int> & s_v, vector<int> & s_s_v) {
        if (!k) {
            return 0;
        }
        int cnt = 0;
        // 시작 인덱스를 늘려감으로 써, 원소의 포함 여부를 선택한다.
        for (int i = c; i < (int) s_v.size(); i++) {
            s_s_v.push_back(s_v[i]);
            cnt += subset_with_start_idx(i + 1, k - 1, s_v, s_s_v);
            cnt++;
            dump_vec(s_s_v, true);
            s_s_v.pop_back();
        }
        return cnt;
    }


    int subset_with_select(int c, int k, vector<int> & s_v, vector<int> & s_s_v) {
        if (!k) {
            return 0;
        }

        int cnt = 0;
        s_s_v.push_back(s_v[c]);
        cnt += subset_with_select(c + 1, k - 1, s_v, s_s_v);
        dump_vec(s_s_v, true);
        cnt++;
        s_s_v.pop_back();

        cnt += subset_with_select(c + 1, k - 1, s_v, s_s_v);

        return cnt;
    }

    void test(int n) {
        vector<int> s_v;
        for (int i = 1; i <= n; i++) {
            s_v.push_back(i);
        }
        vector<int> s_s_v;
        cout << "* subset_with_start_idx for ";
        dump_vec(s_v, true);
        int r = subset_with_start_idx(0, n, s_v, s_s_v);

        cout << "* subset_with_select for ";
        dump_vec(s_v, true);
        int r2 = subset_with_select(0, n, s_v, s_s_v);

        cout << "number of subset: " << r << ", " << r2 << endl;
        cout << endl;
    }
}

void test_a01_01_subset_all() {
    PRINT_FUNC_NAME;
    a01_01::test(1);
    a01_01::test(2);
    a01_01::test(3);
    a01_01::test(4);
}
