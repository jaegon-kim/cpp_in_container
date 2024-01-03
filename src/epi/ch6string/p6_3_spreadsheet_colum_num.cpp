#include <iostream>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_3 {

    int ctoi(char c) {
        if (c >= 'A' && c <= 'Z') {
            return c - 'A' + 1;
        }
        return 0;
    }

    int colum_str2int(const string & col) {

        int v = 0;
        for (size_t i = 0; i < col.length(); i++) {
            if (i) {
                v *= 26;
            }
            v += ctoi(col[i]);
        }
        return v;
    }

    void test(const string & col) {
        int v = colum_str2int(col);
        cout << col << ": " << v << endl;
    }
}

void p6_3_spreadsheet_colum_num() {
    PRINT_FUNC_NAME;
    p6_3::test("A");
    p6_3::test("D");
    p6_3::test("AA");
    p6_3::test("ZZ");
}
