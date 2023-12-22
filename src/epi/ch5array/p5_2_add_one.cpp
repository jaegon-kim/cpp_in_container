#include <iostream>
#include <vector>

using namespace std;

namespace p5_2 {

    const vector<int> add_one_vec(const vector<int> v) {
        vector<int> a = v;
        size_t len = a.size();
        int carry = 1; // add one on the last location
        for (int i = len - 1; i >= 0; i--) {
            int v = a[i] + carry;
            a[i] = v % 10;
            carry = v / 10;
        }
        if (carry) {
            a.insert(a.begin(), carry);
        }
        return a;
    }

    void dump(const vector<int>& a, bool nl) {
        size_t len = a.size();
        cout << "";
        for (size_t i = 0; i < len; i++) {
            cout << a[i] << "";
        }
        cout << "";
        if (nl) {
            cout << endl;
        }
    }

    void test(const vector<int>& a) {
        dump(a, false);
        cout << " + 1 = ";
        p5_2::dump(p5_2::add_one_vec(a), true);
    }

}

void test_p5_2_add_one() {
    cout << " * " << __func__ << endl;
 
    p5_2::test(vector<int>{1, 2, 3, 4});
    p5_2::test(vector<int>{9, 2, 3, 9});
    p5_2::test(vector<int>{9, 9, 9, 9});

}