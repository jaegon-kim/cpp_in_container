#include <iostream>
#include "utility/dump.hpp"
#include <unordered_set>
#include <list>
#include <vector>

using namespace std;

namespace p15_03 {

    int safe_place(vector<pair<int, int>> & vec_loc, int cur, int end, int depth, 
                set<int> & set_i, set<int> & set_j, set<int> & set_d, set<int> & set_s,
                vector<pair<int, int>> & vec_path) {
        if (!depth) {
            dump_vec_of_pair(vec_path, true);
            return 1;
        }
        int tot_cnt = 0;
        for (int c = cur; c <= end; c++) {

            int i = vec_loc[c].first;
            int j = vec_loc[c].second;
            int diff = i - j;
            int sum = i + j;

            if (set_i.find(i) == set_i.end()) {
                continue;
            }

            if (set_j.find(j) == set_j.end()) {
                continue;
            }

            if (set_d.find(diff) == set_d.end()) {
                continue;
            }

            if (set_s.find(sum) == set_s.end()) {
                continue;
            }

            set_i.erase(i);
            set_j.erase(j);
            set_d.erase(diff);
            set_s.erase(sum);

            vec_path.push_back(vec_loc[c]);
            tot_cnt += safe_place(vec_loc, c + 1, end, depth - 1, set_i, set_j, set_d, set_s, vec_path);
            vec_path.pop_back();

            set_i.emplace(i);
            set_j.emplace(j);
            set_d.emplace(diff);
            set_s.emplace(sum);
        }

        return tot_cnt;
    } 


    void test(int n) {
        cout << endl;
        cout << n << " x " << n << " chess board" << endl;
        set<int> set_i;
        for (int i = 0; i < n; i++) {
            set_i.emplace(i);
        }

        set<int> set_j;
        for (int j = 0; j < n; j++) {
            set_j.emplace(j);
        }
        set<int> set_d;
        for (int d = -1 * (n - 1); d <= (n - 1); d++) {
            set_d.emplace(d);
        }
        set<int> set_s;
        for (int s = 0; s <= 2 * (n - 1); s++) {
            set_s.emplace(s);
        }
        //dump_set(set_i, true);
        //dump_set(set_j, true);
        //dump_set(set_d, true);
        //dump_set(set_s, true);

        vector<pair<int, int>> vec_loc;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                vec_loc.push_back(make_pair(i, j));
            }
        }
        vector<pair<int, int>> vec_path;
        //dump_vec_of_pair(vec_loc, true);
        int cnt = safe_place(vec_loc, 0, vec_loc.size() - 1, n, set_i, set_j, set_d, set_s, vec_path);
        cout << "possible case: " << cnt << endl;
    }

}

void test_p15_03_safe_qeen() {
    PRINT_FUNC_NAME;
    for (int i = 1; i <= 10; i++) {
        p15_03::test(i);
    }
}

