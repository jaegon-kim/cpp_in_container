#include <iostream>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_4 {

    void test(const string & str) {
        string n = "";
        for (size_t i = 0; i < str.length(); i++) {
            char c = str[i];
            switch(c) {
                case 'a':
                    n.push_back('d');
                    n.push_back('d');
                    break;
                case 'b':
                    break;
                default:
                    n.push_back(c);
            }
        }
        cout << n << endl;
    }
}

void test_p6_4_replace_rm() {
    PRINT_FUNC_NAME;
    p6_4::test("aa");
    p6_4::test("abcdeaff");
}