#include <iostream>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_8 {

    int c2i(char c) {
        switch(c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        return -1;
    }

    int rnum2i(const string & rnum) {
        int len = rnum.length();
        int prev_v = 0;
        int sum = 0;
        for (int i = len - 1; i >= 0; i--) {
            int v = c2i(rnum[i]);

            if (v >= prev_v) {
                sum += v;
                prev_v = v;
            } else {
                sum -= v;
                prev_v = 0;
            }
        }
        return sum;
    }

    void test(const string & rnum) {
        cout << rnum << " -> " << rnum2i(rnum) << endl;
    }
}

void test_p6_8_roman_to_i() {
    PRINT_FUNC_NAME;
    p6_8::test("XXXXXIIIIIIIII");
    p6_8::test("LVIIII");
    p6_8::test("LIX");
}
