#include <iostream>
#include <string>
#include "utility/dump.hpp"

using namespace std;


namespace p6_2 {

    static inline int ctoi(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'A' && c <= 'F') {
            return 10 + (c - 'A');
        } else if (c >= 'a' && c <= 'f') {
            return 10 + (c - 'a');
        }
        return -1;
    }

    static inline char itoc(int i) {
        if (i >= 0 && i <= 9) {
            return '0' + i;
        } else if (i >= 0xa && i <= 0xf) {
            return 'A' + (i - 0xa);
        }
        return '0';
    }

    int s2dec_int(const string & s, int b) {
        int len = s.length();
        int iv = 0;
        int i = 0;
        bool carry = false;
        if (s[0] == '-') {
            i = 1;
        }
        for (; i < len; i++) {
            if (carry) {
                iv *= b;
            }
            iv += ctoi(s[i]);
            carry = true;
        }
        return (s[0] == '-'? iv * (-1): iv);
    }

    string base_tranform(int i, int b) {
        vector<int> v(0);
        bool negative = false;
        if (i < 0) {
            negative = true;
            i *= (-1);
        }

        while(i > 0) {
            v.emplace_back(i % b);
            i /= b;
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
            s.push_back(itoc(v[j]));
        }
        return s;
    }


    void test(const string & num, int b1, int b2) {
        int i = s2dec_int(num, b1);
        cout << num << " --> " << i << ", ";
        cout << i << " --> " << base_tranform(i, b2) << endl;
    }
}


void test_p6_2_base_transform() {
    PRINT_FUNC_NAME;
    p6_2::test("615", 7, 13);
}
