#include <iostream>
#include "utility/dump.hpp"

using namespace std;

namespace p16_01 {

    size_t possible_point(int score, const vector<int> & v_p, size_t idx, vector<int> & set) {
        if (!score) {
            cout << " ";
            for (size_t i = 0; i < set.size(); i++) {
                if (set[i]) {
                    cout << v_p[i] << " * " << set[i];
                    if ((i + 1) != (set.size())) {
                         cout << " + ";
                    }
                }
            }
            cout << endl;
            return 1;
        }

        if (idx == v_p.size()) {
            return 0;
        }

        size_t count = 0;
        for (int i = 0; (v_p[idx] * i) <= score; i++) {
            set.push_back(i);
            count += possible_point(score - (v_p[idx] * i), v_p, idx + 1, set);
            set.pop_back();
        }

        return count;
    }

    void test(int score) {
        vector<int> set;
        size_t count = possible_point(score, vector<int>{2, 3, 7}, 0, set);
        cout << "number of case = " << count << " for score " << score << endl;
    }
}

void test_p16_01_possible_point_case() {
    PRINT_FUNC_NAME;
    //p16_01::test(11);
    //p16_01::test(12);
    //p16_01::test(64);
    for (int i = 1; i < 12; i++) {
        p16_01::test(i);
    }
    p16_01::test(1128);
}

