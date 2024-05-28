#include <iostream>
#include <unordered_set>
#include <string>
#include "utility/dump.hpp"
using namespace std;

namespace p16_07 {

    bool parse_dic_topdown(const string & name, const unordered_set<string> & dic, size_t s, size_t e, vector<string> & tokens) {
        
        if (s == name.size()) {
            return true;
        }

        for (size_t i = e; i <= name.length(); i++) {
            size_t len = i - s;
            string s_str = name.substr(s, len);
            if (dic.find(s_str) != dic.end()) {
                tokens.push_back(s_str);
                bool r = parse_dic_topdown(name, dic, i, i + 1, tokens);
                if (r) {
                    return true;
                }
                tokens.pop_back();
            }
        }

        return false;
    }

    void test(string name, unordered_set<string> & dic) {
        vector<string> tokens;
        bool r = parse_dic_topdown(name, dic, 0, 1, tokens);
        dump_vec(tokens, true);
        cout << r << endl;
    }
}

void test_p16_07_bedbathandbeyond() {
    PRINT_FUNC_NAME;

    string str = "bedbathandbeyond";
    cout << "str: " << str << endl;
    cout << "str.substr(0, 1): " << str.substr(0, 1) << endl;
    cout << "str.substr(1, 2): " << str.substr(1, 2) << endl;
    cout << "str.substr(2, 2): " << str.substr(2, 2) << endl;

    unordered_set<string> dic;
    dic.emplace("bed");
    dic.emplace("bath");
    dic.emplace("bat");
    dic.emplace("and");
    dic.emplace("beyond");
    dic.emplace("a");
    dic.emplace("man");
    dic.emplace("plan");
    dic.emplace("canal");

    p16_07::test("bedbathandbeyond", dic);
    p16_07::test("bedbathandbeyonde", dic);
    p16_07::test("amanaplanacanal", dic);
}