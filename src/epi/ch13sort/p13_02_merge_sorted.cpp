#include <iostream>

#include "utility/dump.hpp"

using namespace std;

namespace p13_02 {

    template <typename T>
    void dump_arr(T a[], size_t len, bool nl) {
        cout << "{";
        for(size_t i = 0; i < len; i++) {
            cout << a[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void sorted_merge(int a[], size_t len_a, size_t size_a, int b[], size_t len_b) {
        if ((len_a + len_b) > size_a) {
            return;
        }

        int i_a = len_a - 1;
        int i_b = len_b - 1;
        int i_s = len_a + len_b - 1;

        while(i_a >= 0 || i_b >= 0) {
            if (i_a < 0) {
                a[i_s--] = b[i_b--];
            } else if (i_b < 0) {
                a[i_s--] = a[i_a--];
            } else {
                if (a[i_a] > b[i_b]) {
                    a[i_s--] = a[i_a--];
                } else {
                    a[i_s--] = b[i_b--];
                }
            }
        }
    }

    void test(int a[], size_t len_a, size_t size_a, int b[], size_t len_b) {
            dump_arr(a, len_a, true);
            dump_arr(b, len_b, true);
            sorted_merge(a, len_a, size_a, b, len_b);
            dump_arr(a, len_a + len_b, true);

       }
}

void test_p13_02_merge_sorted() {
    PRINT_FUNC_NAME;
    int a1[] = {5, 13, 17, 0, 0, 0, 0, 0};
    int a2[] = {3, 7, 11, 19};
    p13_02::test(a1, 3, 8, a2, 4);
}