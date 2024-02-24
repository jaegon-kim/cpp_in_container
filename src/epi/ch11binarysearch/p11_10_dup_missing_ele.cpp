#include <iostream>
#include "utility/dump.hpp"
#include <vector>
#include <bitset>

using namespace std;

namespace p11_10 {

    void test_find_missing_1_with_sum(const vector<int> & v, int max) {
        int v_sum = 0;
        for(int e: v) {
            v_sum += e;
        }
        int sum = (max + 1) * max / 2;
        cout << "missing: " << (sum - v_sum) << endl;
    }

    void test_find_missing_1_with_xor(const vector<int> & v, int max) {
        int v_xor = v[0];
        for(size_t i = 1; i < v.size(); i++) {
            v_xor = v_xor ^ v[i];
        }

        int m_xor = 0;
        for(int i = 1; i <= max; i++) {
            m_xor = m_xor ^ i;
        }

        cout << bitset<32>(v_xor) << endl;
        cout << bitset<32>(m_xor) << endl;
        cout << "missing: " << (v_xor ^ m_xor) << endl;
    }

    // 이해가 잘 되지는 않지만 일단 따라서 구현함
    pair<int, int> find_dup_missing(const vector<int>& v) {
        int miss_xor_dup = 0;
        for(int i = 0; i < (int) v.size(); i++) {
            miss_xor_dup ^= i ^ v[i]; 
        }

        int differ_bit = miss_xor_dup &(~(miss_xor_dup - 1));
        int miss_or_dup = 0;
        for (int i = 0; i < (int) v.size(); ++i) {
            if (i & differ_bit) {
                miss_or_dup ^= i;
            }
            if (v[i] & differ_bit) {
                miss_or_dup ^= v[i];
            }
        }

        return make_pair(miss_or_dup, miss_or_dup ^ miss_xor_dup);
    }

    void test(const vector<int> & v) {
        auto p = find_dup_missing(v);
        cout << p.first << ", " << p.second << endl;
    }

}

void test_p11_10_dup_missing_ele() {
    PRINT_FUNC_NAME;

    p11_10::test_find_missing_1_with_sum(vector<int> {5, 3, 0, 1, 2}, 5);
    p11_10::test_find_missing_1_with_xor(vector<int> {5, 3, 0, 1, 2}, 5);
    p11_10::test(vector<int> {5, 3, 0, 3, 1, 2});

}