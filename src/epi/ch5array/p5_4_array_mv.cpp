#include <iostream>
#include <vector>

using namespace std;

namespace p5_4 {

    bool is_reachable_cs(const vector<int> & a, int c, int g) {

        if (c != g && a[c] == 0) {
            return false;
        }

        if ((c + a[c]) >= g) {
            return true;
        }

        for (int i = 1; i <= a[c]; i++) {
            if (is_reachable_cs(a, c + i, g)) {
                return true;
            }
        }
        return false;
    } 
    enum memo_state { INIT, REACHABLE, NOT_REACHABLE};

    bool is_reachable_memo(const vector<int> & a, int c, int g, vector<memo_state> & m) {

        switch(m[c]) {
            case memo_state::REACHABLE:
                return true;
            case memo_state::NOT_REACHABLE:
                return false;
        }

        if (c != g && a[c] == 0) {
            m[c] = memo_state::NOT_REACHABLE;
            return false;
        }

        if ((c + a[c]) >= g) {
            m[c] = memo_state::REACHABLE;
            return true;
        }

        for (int i = 1; i <= a[c]; i++) {
            if (is_reachable_cs(a, c + i, g)) {
                m[c] = memo_state::REACHABLE;
                return true;
            }
        }
        m[c] = memo_state::NOT_REACHABLE;
        return false;

    }

    void dump(const vector<int>& a, bool nl) {
        size_t len = a.size();
        cout << "{";
        for (size_t i = 0; i < len; i++) {
            cout << a[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }


    void test_is_reachable(const vector<int> a) {
        bool rslt = is_reachable_cs(a, 0, a.size() - 1);

        vector<memo_state> memo = vector<memo_state>(a.size(), memo_state::INIT);
        bool rslt2 = is_reachable_memo(a, 0, a.size() - 1, memo);

        dump(a, false);
        cout << " cs: " << (rslt? "[reachable]": "[not rechable]");
        cout << " memo: " << (rslt2? "[reachable]": "[not rechable]");
        cout << endl;
    }

}


void test_p5_4_array_mv() {
    cout << " * " << __func__ << endl;

    p5_4::test_is_reachable(vector<int>{0});
    p5_4::test_is_reachable(vector<int>{1});
    p5_4::test_is_reachable(vector<int>{0, 0});
    p5_4::test_is_reachable(vector<int>{3, 3, 1, 0, 2, 0, 1});
    p5_4::test_is_reachable(vector<int>{3, 2, 0, 0, 2, 0, 1});

}