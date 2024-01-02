#include <iostream>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_1 {

    int stoi(string & s) {
        int len = s.length();
        int iv = 0;
        int i = 0;
        bool carry = false;
        if (s[0] == '-') {
            i = 1;
        }
        for (; i < len; i++) {
            if (carry) {
                iv *= 10;
            }
            iv += (s[i] - '0');
            carry = true;
        }
        return (s[0] == '-'? iv * (-1): iv);
    }

    string itos(int i) {
        vector<int> v(0);
        bool negative = false;
        if (i < 0) {
            negative = true;
            i *= (-1);
        }

        while(i > 0) {
            v.emplace_back(i % 10);
            i /= 10;
        }

        int len = v.size();

        if (!len) {
            return "0";
        }

        string s = "";
        if (negative) {
            s.push_back('-');
        }
        for (int j = len - 1; j >= 0; j--) {
            s.push_back('0' + v[j]);
        }
        return s;
    }

    void test(string s) {
        int i = stoi(s);
        cout << s << " -stoi-> " << i << ", ";
        string s2 = itos(i);
        cout << i << " -itos-> " << s2 << endl;
    }
}

void test_p6_1_itos_stoi() {
    PRINT_FUNC_NAME;
    p6_1::test("0");
    p6_1::test("615");
    p6_1::test("10610");
    p6_1::test("-10610");
}
