#include <iostream>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_5 {

    bool is_alphabet(const char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool is_palindrom(const string & str) {
        int s = 0;
        int e = str.length() - 1;
        while(s < e) {
            if (!is_alphabet(str[s])) {
                s++;
                continue;
            }
            if (!is_alphabet(str[e])) {
                e--;
                continue;
            }
            if (str[s] != str[e]) {
                return false;
            }
            s++;
            e--;
        }
        return true;
    }

    void test(const string & str, bool is_palin) {
        bool rslt = is_palindrom(str);
        cout << (rslt == is_palin? "[success] ": "[failure] ");
        cout << str << " is " << (rslt? "palindrom": "not palindrom") << endl;
    }
}

void test_p6_5_palindrom() {
    PRINT_FUNC_NAME;

    p6_5::test("a", true);
    p6_5::test("abcdedcba", true);
    p6_5::test("abcddcba", true);
    p6_5::test("a!!!bcd@e$dcb%%%  a", true);

}
