#include <iostream>
#include <vector>
#include <bitset>

#include "utility/dump.hpp"

using namespace std;

namespace p14_06 {
    pair<int, int> pop_min(
        const vector<int> &v1, int & idx_1, 
        const vector<int> &v2, int & idx_2, 
        const vector<int> &v3, int & idx_3) {

            pair<int, int> min = make_pair(0x7FFFFFFF, 0);
            if (idx_1 < (int) v1.size() && min.first > v1[idx_1]) {
                min.first = v1[idx_1];
                min.second = 1;
            }

            if (idx_2 < (int) v2.size() && min.first > v2[idx_2]) {
                min.first = v2[idx_2];
                min.second = 2;
            }

            if (idx_3 < (int) v3.size() && min.first > v3[idx_3]) {
                min.first = v3[idx_3];
                min.second = 3;
            }

            switch(min.second) {
                case 1:
                    idx_1++;
                    break;
                case 2:
                    idx_2++;
                    break;
                case 3:
                    idx_3++;
                    break;
            }

            //cout << min.first << ", " << min.second << endl;

        return min;
    }

    vector<pair<int, int>> merge(const vector<int> & v1, const vector<int> &v2, const vector<int> &v3) {

        vector<pair<int, int>> m;
        int idx_1 = 0, idx_2 =0, idx_3 = 0;

        while(true) {
            pair<int, int> min = pop_min(v1, idx_1, v2, idx_2, v3, idx_3);
            if (!min.second) {
                break;
            }
            m.push_back(min);
        }

        return m;
    }

    int diff(int a, int b) {
        if (a > b) {
            return a - b;
        } else {
            return b - a;
        }
    }

    int path_len(vector<pair<int, int>>  & sv) {
        return diff(sv[0].first, sv[1].first) + diff(sv[1].first, sv[2].first);
    }
    
    vector<pair<int, int>> find_shortest_path(vector<pair<int, int>> & m) {

        int len_m = m.size();

        int min_len = 0x7FFFFFFF;

        vector<pair<int, int>> shortest_pv;

        for (int i = 0; i < len_m; i++) {

            vector<pair<int, int>> pv;
            int mask = 0x7;
            mask ^= (0x1 << (m[i].second -1));
            pv.push_back(m[i]);
            //cout << bitset<sizeof(int)>(mask) << ", " << mask << ", " << m[i].second <<  endl;

            for (int j = i + 1; j < len_m; j++) {
                if (mask & (0x1 << (m[j].second - 1))) {
                    mask ^= (0x1 << (m[j].second - 1));
                    pv.push_back(m[j]);

                    if (!mask) {
                        //dump_vec_of_pair(pv, true);
                        int len = path_len(pv);
                        if (len < min_len) {
                            shortest_pv = pv;
                        }

                        break;
                    }
                }
            }
        }


        return shortest_pv;
    }


    void test(const vector<int> & v1, const vector<int> &v2, const vector<int> &v3) {

        auto m = merge(v1, v2, v3);
        //dump_vec_of_pair(m, true);
        auto shortest_pv = find_shortest_path(m);
        cout << "shortest: ";
        dump_vec_of_pair(shortest_pv, true);


    }

}

void test_p14_06_shortest_path() {
    PRINT_FUNC_NAME; 
    p14_06::test(
        vector<int> {5, 10, 15},
        vector<int> {3, 6, 9, 12, 15},
        vector<int> {8, 16, 24}
    );   
}