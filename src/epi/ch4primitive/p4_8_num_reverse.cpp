#include <iostream>

using namespace std;

int num_reverse_i32(int a) {
    long long r = 0;
    int n = 1;
    if (a < 0) {
        n = -1, a *= -1;
    }

    for ( ;a >= 10; r *= 10) {
        r += (a % 10);
        a /= 10;
    }
    r += a;
    return ((int) r) * n;
}

bool test_num_reverse(int a, int expect) {
    int rslt = num_reverse_i32(a);
    bool success = (rslt == expect);
    cout << "[" << (success? "success": "failure") << "] reverse(" << a << "): " << rslt << endl;
    return success;
}


void test_num_reverse() {
    cout << " * " << __func__ << endl;
    test_num_reverse(0, 0);
    test_num_reverse(9, 9);
    test_num_reverse(12, 21);
    test_num_reverse(1234, 4321);
    test_num_reverse(12345678, 87654321);
    //test_num_reverse(0x7fffffff, 7463847412); // max int
    test_num_reverse(-9, -9);
    test_num_reverse(-12, -21);
    test_num_reverse(-1234, -4321);
    test_num_reverse(-12345678, -87654321);
    //test_num_reverse(-0x7fffffff, -7463847412); // max int
}