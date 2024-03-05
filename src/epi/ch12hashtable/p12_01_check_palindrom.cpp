#include <iostream>
#include <string>
#include <unordered_map>

#include "utility/dump.hpp"

using namespace std;

namespace p12_01 {

    bool check_palindrom(const string & str) {
        unordered_map<char, int> map;

        for (char c: str) {
            if (map.find(c) == map.end()) {
                map.emplace(c, 1);
            } else {
                ++map[c];
            }
        }

        size_t odd_cnt = 0;
        for (auto p: map) {
            cout << p.first << ": " << p.second << endl;
            if (((p.second % 2) != 0) && (++odd_cnt > 1)) {
                return false;
            }
        }
        return true;
    }

    void test(const string & str) {
        cout << "check_palindrom: " << str << endl;
        cout << (check_palindrom(str) ? "true": "false") << endl;
    }

}

void test_p12_01_check_palindrom() {
    PRINT_FUNC_NAME;
    p12_01::test("edified");
    p12_01::test("level");
    p12_01::test("rotator");
    p12_01::test("edifgied");

}

