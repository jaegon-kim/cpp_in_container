#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "utility/dump.hpp"
using namespace std;
namespace p17_04 {

    bool compare(const int & a, const int & b) {
        return a < b;
    }

     vector<tuple<int, int, int>> has_3_sum(vector<int> & v, int sum) {
        sort(v.begin(), v.end(), compare);
        dump_vec(v, true);

        unordered_map<int, size_t> map;
        for (size_t i = 0; i < v.size(); i++) {
            map.emplace(sum - v[i], i);
        }

        vector<tuple<int, int, int>> r_v;

        for(size_t i = 0; i < v.size(); i++) {
            for(size_t j = 0; j < v.size(); j++) {
                int s = v[i] + v[j];
                if (map.find(s) != map.end()) {
                    auto t = make_tuple(v[i], v[j], v[map[s]]);
                    r_v.push_back(t);
                }
            }
        }

        return r_v;
    }

    void dump(const vector<tuple<int, int, int>> & v, bool nl) {
        for (auto t: v) {
            cout << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << endl;
        }
        if (nl) {
            cout << endl;
        }
    }

    void test(const vector<int> & i_v, int sum) {
        vector<int> v = i_v;
        auto r = has_3_sum(v, sum);
        dump(r, true);
    }
}

void test_p17_04_has_3_sum() {
    PRINT_FUNC_NAME;
    p17_04::test(vector<int> {11, 2, 5, 7, 3}, 21);
}
