#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p17_07 {

    pair<int, int> max_waterpool_nlogn(const vector<int> & v) {
        int max = 0, max_i = 0, max_j = 0;
        for (size_t i = 0; i < v.size() ; i++) {
            for (size_t j = v.size() - 1; j > i; j--) {
                int s = v[i] * (j - i);
                if (max >= s) {
                    break;
                }

                if (v[j] >= v[i]) {
                    if (max < s) {
                        max = s;
                        max_i = i;
                        max_j = j;
                    }
                    break;
                }
            }
        }
        return make_pair(max_i, max_j);
    }

    pair<int, int> max_waterpool_n(const vector<int> & v) {
        int max = 0, max_i = 0, max_j = 0;
        size_t i = 0, j = v.size() - 1;

        while(i < j) {
            int h = (v[i] <= v[j]? v[i]: v[j]);
            int s = h * (j - i);
            if (max < s) {
                max = s;
                max_i = i;
                max_j = j;
            }

            if (v[i] <= v[j]) {
                i++;
            } else {
                j--;
            }
        }

        return make_pair(max_i, max_j);
    }

    void test(const vector<int> & v) {
        auto r_nlogn = max_waterpool_nlogn(v);
        cout << "nlogn: " << r_nlogn.first << ", " << r_nlogn.second << endl;

        auto r_n = max_waterpool_n(v);
        cout << "n    : " << r_n.first << ", " << r_n.second << endl;
    }
}

void test_p17_07_max_waterpool() {
    PRINT_FUNC_NAME;
    p17_07::test(vector<int> {1, 2, 1, 3, 4, 4, 5, 6, 2, 1, 3, 1, 3, 2, 1, 2, 4, 1});
}
