#include <iostream>
#include <unordered_map>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p15_02 {

    void find(unordered_map<char, vector<char>> & map, const string & nlist, size_t idx, string str, vector<string> & v) {
        if (idx >= nlist.size()) {
            v.push_back(str);
            return;
        }

        if (map.find(nlist[idx]) == map.end()) {
            find(map, nlist, idx + 1, str, v);
            return;
        }

        vector<char> ch_list = map[nlist[idx]];
        for(char c: ch_list) {
            find(map, nlist, idx + 1, str + c, v);
        }
    }

    vector<string> mneumonics(unordered_map<char, vector<char>> & map, const string & nlist) {
        vector<string> v;
        find(map, nlist, 0, "", v);
        return v;
    }

    void test() {
        unordered_map<char, vector<char>> map;
        map.emplace('2', vector<char>{'A', 'B', 'C'});
        map.emplace('3', vector<char>{'D', 'E', 'F'});
        map.emplace('4', vector<char>{'G', 'H', 'I'});
        map.emplace('5', vector<char>{'J', 'K', 'L'});
        map.emplace('6', vector<char>{'M', 'N', 'O'});
        map.emplace('7', vector<char>{'P', 'Q', 'R', 'S'});
        map.emplace('8', vector<char>{'T', 'U', 'V'});
        map.emplace('9', vector<char>{'W', 'X', 'Y', 'Z'});

        dump_vec(mneumonics(map, "123"), true);
        dump_vec(mneumonics(map, "2276696"), true);

    }
}

void test_p15_02_mnemonics() {
    PRINT_FUNC_NAME;
    p15_02::test();
}