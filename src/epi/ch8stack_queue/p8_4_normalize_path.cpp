#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <optional>

#include "utility/dump.hpp"


using namespace std;

namespace p8_4 {

    vector<string> parse(const string & str) {
        vector<string> v;
        size_t len = str.length();
        string token = "";
        for(size_t i = 0; i < len; i++) {
            char c = str[i];
            if (i && c == '/') {
                v.emplace_back(token);
                token = "";
            } else {
                token.push_back(c);
            }            
        }
        if (token.length()) {
            v.emplace_back(token);
        }
        return v;
    }

    optional<string> normalize_path(const vector<string> & v) {
        size_t len = v.size();
        list<string> l;
        for (size_t i = 0; i < len; i++) {
            string token = v[i];
            if (token.compare(".") == 0) {
                // do nothing
            } else if (token.compare("..") == 0) {
                if (l.empty()) {
                    return nullopt;
                }
                l.pop_front();
            } else {
                l.push_front(token);
            }
        }

        //dump_list<string>(l, true);

        string final_path = "";
        len = l.size();
        for (size_t i = 0; i < len; i++) {
            if (i) {
                final_path.append("/");
            }
            final_path.append(l.back());
            l.pop_back();
        }

        return final_path;
    }

    void test(const string & path) {
        vector<string> v = parse(path);
        cout << "path           : " << path << endl;
        //dump_vec<string>(v, true);
        auto opt_path = normalize_path(v);
        cout << "normalized path: " << opt_path.value_or("invalid path") << endl;
    }
}

void test_p8_4_normalize_path() {
    PRINT_FUNC_NAME;
    p8_4::test("output/world output/.././.o/src/epi/ch4primitive/p4_10_random_num_bit_op.o");
    p8_4::test("output/world output/.././../../../.o/src/epi/ch4primitive/p4_10_random_num_bit_op.o");
    p8_4::test("/output/world output/.o/src/epi/ch4primitive/p4_10_random_num_bit_op.o");
    p8_4::test("../output/world output/.o/src/epi/ch4primitive/p4_10_random_num_bit_op.o");

}