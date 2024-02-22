#include <iostream>
#include "utility/dump.hpp"

#include <vector>
#include <queue>
#include <functional>

using namespace std;

namespace p11_8 {

    int kth_big(const vector<int> & v, size_t k) {
        priority_queue<int, vector<int>, function<bool (int, int)>> pq (
            [] (const int & a, const int & b) {
                return a >= b;
            }
        );

        for (size_t i = 0; i < v.size(); i++) {
            if (pq.size() < k) {
                pq.emplace(v[i]);
            } else {
                if (pq.top() < v[i]) {
                    pq.pop();
                    pq.emplace(v[i]);
                }
            }
            //cout << pq.top() << endl;
        }

        return pq.top();
    }

    void test(const vector<int> & v, size_t k) {
        int ret = kth_big(v, k);
        cout << "(" << k << ") th big num: " << ret << " in ";
        dump_vec<int>(v, true);
    }
}

void test_p11_8_kth_big() {
    PRINT_FUNC_NAME;
    p11_8::test(vector<int> {3, 2, 1, 5, 4}, 1);
    p11_8::test(vector<int> {3, 2, 1, 5, 4}, 2);
    p11_8::test(vector<int> {3, 2, 1, 5, 4}, 3);

}