#include <iostream>
#include <string>
#include <utility/dump.hpp>

using namespace std;

namespace p6_10 {

    void test(const string & str) {
        size_t len = str.length();
        string snake_str = "";
        for (size_t i = 1; i < len; i+= 4) {
            snake_str.push_back(str[i]);
        }

        for (size_t i = 0; i < len; i+= 2) {
            snake_str.push_back(str[i]);
        }

        for (size_t i = 3; i < len; i+= 4) {
            snake_str.push_back(str[i]);
        }

        cout << str << " -> " << snake_str << endl;
    }
}


void test_p6_10_snake_string() {
    PRINT_FUNC_NAME;
    p6_10::test("Hello_World!");
}