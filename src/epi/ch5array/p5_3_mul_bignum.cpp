#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace p5_3 {

    const vector<int> mul(vector<int> a, vector<int> b) {
        int alen = a.size(), blen = b.size();
        vector<int> r = vector<int>(alen + blen, 0);
        int sign = (a[0] * b[0]) < 0 ? -1: 1;

        a[0] = abs(a[0]);
        b[0] = abs(b[0]);

        for (int i = alen - 1; i >= 0; i--) {
            for (int j = blen - 1; j >= 0; j--) {
                r[i + j + 1] += a[i] * b[j];
                r[i + j] += r[i + j + 1] / 10; // carry
                r[i + j + 1] %= 10;
            }
        }

        if (r[0] != 0) {
            r[0] *= sign;
        } else {
            r[1] *= sign;
            r.erase(r.begin());
        }

        return r;
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

    void test(vector<int> a, vector<int> b) {
        vector<int> r = mul(a, b);
        dump(a, false);
        cout << " x ";
        dump(b, false);
        cout << " = ";
        dump(r, false);
        cout << endl;
    }

}


void test_p5_3_mul_bignum() {
    cout << " * " << __func__ << endl;
    vector<int> a, b;
    a = {1, 2, 3};
    b = {1, 2, 3};
    p5_3::test(a, b);

    a = {7, 8, 3};
    b = {8, 0, 8};
    p5_3::test(a, b);

    a = {1, 9, 3, 7, 0, 7, 7, 2, 1};
    b = {-7, 6, 1, 8, 3, 8, 2, 5, 7, 2, 8, 7};
    p5_3::test(a, b);

}
