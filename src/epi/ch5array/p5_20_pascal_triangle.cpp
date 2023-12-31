#include <iostream>
#include <vector>

#include "utility/dump.hpp"

using namespace std;

namespace p5_20 {

    vector<int> pascal_triangle(int n) {

        vector<int> v1(1, 1);
        vector<int> v2(0);

        vector<int> * prev_ptr = &v1;
        vector<int> * curr_ptr = &v2;

        cout << "n: " << n << endl;
        //cout << "l: 1";
        dump_vec(*prev_ptr, true);

        if (n == 1) {
            return *prev_ptr;
        }

        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < l ; i++) {
                if (i == 0) {
                    curr_ptr->emplace_back(0 + prev_ptr->at(0));
                } else if (i == (l - 1)) {
                    curr_ptr->emplace_back(prev_ptr->at(l - 2) + 0);
                } else {
                    curr_ptr->emplace_back(prev_ptr->at(i) + prev_ptr->at(i-1));
                }
            }

            //cout << "l: " << l;
            dump_vec(*curr_ptr, true);

            vector<int> * tmp_ptr = prev_ptr;
            prev_ptr = curr_ptr;
            curr_ptr = tmp_ptr;
            curr_ptr->clear();
        }

        return *prev_ptr;
    }

    void test(int n) {
        vector<int> r = pascal_triangle(n);
        dump_vec<int>(r, true);
    }
}

void test_p5_20_pascal_triangle() {
    PRINT_FUNC_NAME;

    p5_20::test(7);
}
