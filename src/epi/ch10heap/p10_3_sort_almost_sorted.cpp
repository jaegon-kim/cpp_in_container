#include <iostream>
#include "utility/dump.hpp"

using namespace std;

#include <vector>
#include <queue>
#include <functional>

namespace p10_3 {

    // k : maximum distance which is not sorted
    vector<int> sort(const vector<int> v, size_t k) {
        size_t len = v.size();
        if (len < (k + 1)) {
            cout << "size is too small " << len << endl;
            return v;
        }

        vector<int> s_v;
        priority_queue<
            int, 
            vector<int>,
            function<bool (int, int)>>
        pq(
            [] (const int & a, const int & b) {
                return a >= b;
            }
        );

        for (size_t i = 0; i < len; i++) {
            pq.emplace(v[i]);
            if (pq.size() >= (k + 1)) {
                //cout << pq.top() << ",";
                s_v.push_back(pq.top());
                pq.pop();
            }
        }
        //cout << endl;
        while(!pq.empty()) {
            //cout << pq.top() << ",";
            s_v.push_back(pq.top());
            pq.pop();
        }

        return s_v;
    }

    void test(const vector<int> v, size_t k) {
        vector<int> s_v = sort(v, k);
        dump_vec(s_v, true);
    }
}

void test_p10_3_sort_almost_sorted() {
    PRINT_FUNC_NAME;
    p10_3::test(vector<int> {3, -1, 2, 6, 4, 5, 8}, 2);
}