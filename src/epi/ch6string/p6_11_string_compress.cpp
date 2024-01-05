#include <iostream>
#include <string>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p6_11 {

    string compress(const string & str) {
        size_t len = str.length();

        string nstr = "";
        char prev_c = 0;
        int cnt = 0;

        for (size_t i = 0; i < len; i++) {
            char c = str[i];
            if (c != prev_c) {
                if (prev_c != 0) {
                    nstr.push_back(prev_c);
                    nstr.append(to_string(cnt));
                }
                prev_c = c;
                cnt = 1;
            } else {
                cnt++;
            }
        }
        if (prev_c != 0) {
            nstr.push_back(prev_c);
            nstr.append(to_string(cnt));
        }

        return nstr;
    }

    void test(const string & str) {
        cout << str << " -> " << compress(str) << endl;
    }
}


void test_p6_11_string_compress() {
    PRINT_FUNC_NAME;
    p6_11::test("aaaabcccaa");
}