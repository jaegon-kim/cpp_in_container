#include <iostream>
#include <string>
#include <unordered_map>

#include "utility/dump.hpp"

using namespace std;

namespace p12_02 {

    bool mail_with_magazine(const string & mail, const string & magazine) {

        unordered_map<char, int> map;

        for (char c: magazine) {
            if (map.find(c) == map.end()) {
                map.emplace(c, 1);
            } else {
                ++map[c];
            }
        }

        for (char c: mail) {
            if (map.find(c) == map.end()) {
                cout<< "not existing char " << c << endl;
                return false;
            } else {
                if (map[c] > 0) {
                    --map[c];
                } else {
                    cout<< "not enough char " << c << endl;
                    return false;
                }
            }
        }
        return true;
    }

    void test(const string & mail, const string & magazine) {
        cout << "mail    : " << mail << endl;
        cout << "magazine: " << magazine << endl;
        cout << (mail_with_magazine(mail,magazine) ? "true": "false") << endl;
    }
}

void test_p12_02_anony_mail_with_magazine() {
    PRINT_FUNC_NAME;
    p12_02::test("hello world", "hello mr kim welcome to the this workshop");
    p12_02::test("hello world", "hello mr kim welcome to the this workshop today");
}