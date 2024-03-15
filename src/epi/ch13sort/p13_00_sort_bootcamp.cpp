#include <iostream>
#include <algorithm>
#include <ctime>

#include "utility/dump.hpp"

using namespace std;


namespace p13_00 {

    template <typename T>
    bool compare(T a, T b) {
        return a > b;
    }

    void test() {

        srand((int)time(NULL));
        vector<int> v;
        size_t len = 10;
        for (size_t i = 0; i < len; i++) {
            v.push_back(rand() % 10);
        }

        dump_vec(v, true);

        sort(v.begin(), v.end());
        dump_vec(v, true);

        sort(v.begin(), v.end(), greater<int>());
        dump_vec(v, true);

        sort(v.begin(), v.end(), less<int>());
        dump_vec(v, true);

        sort(v.begin(), v.end(), compare<int>);
        dump_vec(v, true);
    }

}

void test_p13_00_sort_bootcamp() {
    PRINT_FUNC_NAME;
    p13_00::test();
}
