#include <iostream>
#include "utility/dump.hpp"

#include <vector>
#include <queue>
#include <functional>

using namespace std;

namespace p10_4 {

    vector<int> nearest_k_star(const vector<int> v, size_t k) {
        size_t len = v.size();
        if (len < k) {
            return v;
        }

        vector<int> nearest;
        priority_queue<
            int,
            vector<int>,
            function<bool (int, int)>>
        pq (
            [] (const int & a, const int & b) {
                return a <= b;
            }
        );

        for (size_t i = 0; i < len; i++) {
            if (pq.size() < k) {
                pq.emplace(v[i]);
            } else {
                if (v[i] < pq.top()) {
                    pq.pop();
                    pq.emplace(v[i]);
                }
            }
        }

        while(!pq.empty()) {
            nearest.push_back(pq.top());
            pq.pop();
        }

        return nearest;
    }

    void test() {
        vector<int> nearest = nearest_k_star(vector<int> {3, -1, 2, 6, 0, 4, 5, -10, 8}, 3);
        dump_vec(nearest, true);
    }
}

void test_p10_4_nearest_start() {
    PRINT_FUNC_NAME;
    p10_4::test();
}