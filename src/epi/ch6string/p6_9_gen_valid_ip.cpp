#include <iostream>
#include <vector>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_9 {

    int s2i(const string & str, int s_idx, int e_idx) {
        int num = 0;
        for (int i = s_idx; i <= e_idx; i++) {
            if (i > s_idx) {
                num *= 10;
            }
            num += (str[i] - '0');
        }
        return num;
    }

    bool valid(int num) {
        return (num >= 0) && (num <= 255 );
    }

    void dump_valid_ip(vector<int> & valid_ip) {
        size_t len = valid_ip.size();
        for (size_t i = 0; i < len; i++) {
            cout << valid_ip[i];
            if (i != (len - 1)) {
                cout << ".";
            }
        }
        cout << endl;
    }

    void ip_traverse(const string & ip, int s_idx, int depth, vector<int> & valid_ip) {

        if (depth > 2) {
            if ((ip.length() - s_idx) > 3) {
                return;
            }

            int n = s2i(ip, s_idx, ip.length() - 1);
            if (n && valid(n)) {
                valid_ip.push_back(n);
                dump_valid_ip(valid_ip);
                valid_ip.pop_back();
            }
            return;

        } else {
            for (int i = 0; i < 3; i++) {
                int n = s2i(ip, s_idx, s_idx + i);
                if (valid(n)) {
                    valid_ip.push_back(n);
                    ip_traverse(ip, s_idx + i + 1, depth + 1, valid_ip);
                    valid_ip.pop_back();
                }
            }
        }
    }

    void test(const string & ip) {
        vector<int> valid_ip(0);
        ip_traverse(ip, 0, 0, valid_ip);
    }
}


void test_p6_9_gen_valid_ip() {
    PRINT_FUNC_NAME;

    p6_9::test("19216811");
}