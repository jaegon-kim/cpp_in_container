#include <iostream>
#include "utility/dump.hpp"
#include <unordered_set>
#include <list>
#include <vector>

using namespace std;

namespace p15_03_1 {

    int safe_place(list<int> & list_j, int i, int n, set<int> & set_d, set<int> & set_s, 
                    vector<pair<int, int>> & vec_path) {

        if (i == n) {
            //dump_vec_of_pair(vec_path, true);
            return 1;
        }

        int tot_cnt = 0;
        int len_list_j = (int) list_j.size();

        for (int c = 0; c < len_list_j; c++) {
            int j = list_j.front();
            list_j.pop_front();

            int diff = i - j;
            int sum = i + j;
            if (set_d.find(diff) == set_d.end()) {
                list_j.push_back(j);
                continue;
            }

            if (set_s.find(sum) == set_s.end()) {
                list_j.push_back(j);
                continue;
            }
            set_d.erase(diff);
            set_s.erase(sum);

            vec_path.push_back(make_pair(i, j));
            tot_cnt += safe_place(list_j, i + 1, n, set_d, set_s, vec_path);
            vec_path.pop_back();

            list_j.push_back(j);
            set_d.emplace(diff);
            set_s.emplace(sum);
        }

        return tot_cnt;
    } 


    void test(int n) {
        cout << endl;
        cout << n << " x " << n << " chess board" << endl;

        list<int> list_j;
        for (int j = 0; j < n; j++) {
            list_j.push_back(j);
        }
        set<int> set_d;
        for (int d = -1 * (n - 1); d <= (n - 1); d++) {
            set_d.emplace(d);
        }
        set<int> set_s;
        for (int s = 0; s <= 2 * (n - 1); s++) {
            set_s.emplace(s);
        }

        vector<pair<int, int>> vec_path;
        
        int cnt = safe_place(list_j, 0, n, set_d, set_s, vec_path);
        cout << "possible case: " << cnt << endl;
    }

}

void test_p15_03_1_safe_qeen_enhance() {
    PRINT_FUNC_NAME;
    for (int i = 1; i <= 10; i++) {
        p15_03_1::test(i);
    }
    //p15_03_1::test(11);
}

