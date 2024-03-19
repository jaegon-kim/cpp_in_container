#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p13_05 {

    bool compare(int a, int b) {
        return a < b;
    }

    void search(vector<int> & v, vector<bool> & s_map, int sum, unordered_set<int> & sum_set, int & max) {
        sum_set.emplace(sum);
        if (sum > max) {
            max = sum;
        }
        size_t len = v.size();
        for(size_t i = 0; i < len; i++) {
            if (!s_map[i]) {
                s_map[i] = true;
                search(v, s_map, sum + v[i], sum_set, max);
                s_map[i] = false;
            }
        }
    }

    int impossible_min_num(vector<int> v) {
        sort(v.begin(), v.end(), compare);
        vector<bool> s_map(v.size(), false);
        //dump_vec(s_map, true);

        unordered_set<int> sum_set;
        int max = 0;
        search(v, s_map, 0, sum_set, max);
        //dump_set(sum_set, true);

        for(int i = 1; i <= max; i++) {
            if (sum_set.find(i) == sum_set.end()) {
                return i;
            }
        }
        return -1;
    }

    void test(const vector<int> & v) {
        int r = impossible_min_num(v);
        cout << r << endl;
    }
}

void test_p13_05_impossible_min_num() {
    PRINT_FUNC_NAME;
    p13_05::test(vector<int> {1, 1, 1, 1, 1, 5, 10, 25});
    p13_05::test(vector<int> {1, 2, 5});
    p13_05::test(vector<int> {12, 2, 1, 15, 2, 4});

}