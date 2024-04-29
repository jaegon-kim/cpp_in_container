#include <iostream>
#include "utility/dump.hpp"
#include <vector>

using namespace std;

namespace p15_07 {

    void dump_bracket(vector<char> & l, bool nl) {
        for(auto e: l) {
            cout << e;
        }
        if (nl) {
            cout << endl;
        }
    }

    void bracket(size_t o_left, size_t o, vector<char> & l) {
        if (!o_left && !o) {
            dump_bracket(l, true);
            return;
        }
        if (o_left) {
            l.push_back('(');
            bracket(o_left - 1, o + 1, l);
            l.pop_back();
        }
        if (o) {
            l.push_back(')');
            bracket(o_left, o - 1, l);
            l.pop_back();
        }
    }

    void test(size_t n) {
        cout << "# of bracket: " << n << endl; 
        vector<char> l;
        bracket(n, 0, l);
    }
}

void test_p15_07_bracket_pair_set() {
    PRINT_FUNC_NAME;
    p15_07::test(3);
    p15_07::test(4);

}