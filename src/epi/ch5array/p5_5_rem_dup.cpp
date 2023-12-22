#include <iostream>
#include <vector>

using namespace std;

namespace p5_5 {
    vector<int> rem_dup(vector<int> & a) {
        size_t len = a.size();
        if (!len) {
            return a;
        }
        size_t w = 1;
        for (size_t i = 1; i < len; i++) {

            if (a[w-1] != a[i]) {
                a[w++] = a[i];
            }
        }
        for (size_t i = w; i < len; i++) {
            a[i] = 0;
        }
        return a;
    }

    void dump(vector<int>& a, bool nl) {
        cout << "{";
        size_t len = a.size();
        for (size_t i = 0; i < len; i++) {
            cout << a[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void test_rem_dup(const vector<int> & v) {
        vector<int> a = v;
        dump(a, false);
        cout << "-";
        a = rem_dup(a);
        dump(a, true);
    }

}


void test_p5_5_rem_dup() {
    cout << " * " << __func__ << endl;

     p5_5::test_rem_dup(vector<int>{1, 2, 3, 3, 4, 5, 6, 6, 6, 7});
     p5_5::test_rem_dup(vector<int>{1, 2, 2, 2, 2, 3, 4, 5, 6, 6, 6, 7});

}