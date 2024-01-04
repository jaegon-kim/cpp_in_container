#include <iostream>
#include <vector>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_7 {

    vector<string> look_and_say(int n) {
        vector<string> plist(0);
        plist.push_back("1");

        for(int i = 1; i < n; i++) {
            string np = "";
            string & ref_s = plist[i - 1];
            size_t len = ref_s.length();
            char c = 0;
            int cnt = 0;

            for (size_t j = 0; j < len; j++) {
                if (c == ref_s[j]) {
                    cnt++;
                } else {
                    if (c != 0) {
                        np += to_string(cnt);
                        np.push_back(c);
                    }
                    c = ref_s[j];
                    cnt = 1;
                }
            }

            if (c != 0) {
                np += to_string(cnt);
                np.push_back(c);
            }

            plist.push_back(np);
        }

        return plist;
    }

    void test(int n) {
        const vector<string> v = look_and_say(n);
        dump_vec<string>(v, true);
    }

}

void test_p6_7_look_and_say() {
    PRINT_FUNC_NAME;
    p6_7::test(8);
}