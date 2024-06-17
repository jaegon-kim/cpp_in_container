#include <iostream>
#include "utility/dump.hpp"
using namespace std;
namespace p24_01 {

    // 유클리드 호제법
    int gcd_mod(int p1, int p2) {
        int a, b;
        if (p1 > p2) {
            a = p1, b = p2;
        } else {
            a = p2, b = p1;
        }

        int m = a % b;
        if (!m) {
            return b;
        }

        return gcd_mod(b, m);
    }

    int gcd_sub(int p1, int p2) {
        int a, b;
        if (p1 > p2) {
            a = p1, b = p2;
        } else {
            a = p2, b = p1;
        }

        int s = a - b;
        if (!s) {
            return b;
        }

        return gcd_sub(b, s);
    }

    // 곱셈, 나눗셈, 나머지 연산 없이 GCD를 계산
    int gcd_sub2(int p1, int p2) {

        if (p1 == p2) {
            return p1;
        }

        int a, b;
        if (p1 > p2) {
            a = p1, b = p2;
        } else {
            a = p2, b = p1;
        }

        // 음수 짝수 확인
        if (!(a & 0x1) && !(b & 0x1)) {
            return 2 * gcd_sub2(a >> 1, b >> 1);
        } else if (!(a & 0x1) && (b & 0x1)) {
            return gcd_sub2(a >> 1, b);
        } else if ((a & 0x1) && !(b & 0x1)) {
            return gcd_sub2(a , b >> 1);
        } else if ((a & 0x1) && (b & 0x1)) {
            return gcd_sub2(b , a - b);
        }

        return -1;
    }


    void test(int p1, int p2) {
        int r_mod = gcd_mod(p1, p2);
        int r_sub = gcd_sub(p1, p2);
        int r_sub2 = gcd_sub2(p1, p2);
        cout << "gcd(" << p1 << ", " << p2 << "): " <<
                r_mod << "(mod), " <<  
                r_sub << "(sub), " <<
                r_sub2 << "(sub2)" << 
                endl;
    }
}

void test_p24_01_gcd() {
    PRINT_FUNC_NAME;
    p24_01::test(10, 2);
    p24_01::test(2, 10);
    p24_01::test(240, 360);
    p24_01::test(77, 99);
}