#include <iostream>
#include "utility/dump.hpp"

using namespace std;

namespace p15_00 {

    int gcd(int p1, int p2) {
        int a = (p1 > p2 ? p1: p2);
        int b = (p1 < p2 ? p1: p2);
        int m = a % b;
        if (m == 0) {
            return b;
        }
        return gcd(b, m);
    }

    void test_gcd(int a, int b) { 
        int v = gcd(a, b);
        cout << "gcd(" << a << ", " << b << ") = " << v << endl; 
    }
}

void test_p15_00_bootcamp() {
    PRINT_FUNC_NAME;
    p15_00::test_gcd(10, 2);
    p15_00::test_gcd(2, 10);
    p15_00::test_gcd(240, 360);
    p15_00::test_gcd(77, 99);

}
