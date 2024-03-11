#include <iostream>
#include <unordered_map>

#include "utility/dump.hpp"

using namespace std;

namespace p12_09 {

    pair<int, int> longest_continuous_num_seq(const vector<int> vec) {
        int len = vec.size();
        unordered_map<int, int> map; // k: number, v: index
        int min_num = vec[0];
        int max_num = vec[0];

        for (int i = 0; i < len; i++) {
            map.emplace(vec[i], i);
            if (vec[i] < min_num) {
                min_num = vec[i];
            } 
            if (vec[i] > max_num) {
                max_num = vec[i];
            }
        }
        //cout << "min-max: " << min_num << ", " << max_num << endl;
        //dump_map(map, true);
        bool cont = true;
        int s = min_num;
        int max_s = s;
        int max_e = s;
        for (int e = s + 1; e <= max_num; e++) {
            if (map.find(e) == map.end()) {
                cont = false;
            } else {
                if (!cont) {
                    s = e;
                    cont = true;
                }

                if ((max_e - max_s) < (e - s)) {
                    max_s = s;
                    max_e = e;
                }
                //cout << "s: " << s << ", " << "e: " <<  e << endl;
            }
        }

        return make_pair(max_s, max_e);
    }

    void test(const vector<int> vec) {
        auto p = longest_continuous_num_seq(vec);
        cout << p.first << ", " << p.second  << endl;
    }
}

void test_12_09_longest_cont_num_seq() {
    PRINT_FUNC_NAME;
    p12_09::test(vector<int> {3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8});
    p12_09::test(vector<int> {10, 5, 3, 11, 6, 100, 4, 100000000});
}

