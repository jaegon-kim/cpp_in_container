#include <iostream>
#include "utility/dump.hpp"

using namespace std;

#include <vector>
#include <queue>
#include <functional>

using namespace std;

namespace p10_6 {

    vector<int> get_max_k(const vector<int> max_heap, size_t k) {

        priority_queue<int, vector<int>, function<bool (int, int)>>
        max_q([](const int &a, const int &b) {
                return a >= b;
            });

        size_t len = max_heap.size();
        for(size_t i = 0; i < len; i++) {
            if (max_q.size() < k) {
                max_q.emplace(max_heap[i]);
            } else {
                if (max_q.top() < max_heap[i]) {
                    max_q.pop();
                    max_q.emplace(max_heap[i]);
                }
            }
            //cout << max_q.top() << endl;
        }

        vector<int> max_k;
        while(!max_q.empty()) {
            max_k.push_back(max_q.top());
            max_q.pop();
        }

        return max_k;
    }

    void test() {
        vector<int> r_v = get_max_k(vector<int> {561, 314, 401, 28, 156, 359, 271, 11, 3}, 5);
        dump_vec<int>(r_v, true);
    }
}

void test_p10_6_max_k_in_max_heap() {
    PRINT_FUNC_NAME;
    p10_6::test();
}
