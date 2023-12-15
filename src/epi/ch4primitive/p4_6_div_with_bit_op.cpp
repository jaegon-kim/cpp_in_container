#include <iostream>
#include <bitset>

using namespace std;

struct div_rslt {
    unsigned long long div;
    unsigned long long rest;
};

struct div_rslt bitop_div_u64(unsigned long long x, unsigned long long y) {

    int s;
    // 맨 윗자리에서 부터 이진수 나눗셈을 할 위치를 찾음
    // s: 나눗셈을 시작할 맺 윗자리 shift 값
    for ( s = 0; s < 64; s++, y <<= 1) {
        if ( y == 0xffffffffffffffffUL) { // y가 u64에서 최대 값일 경우
            break;
        }
        if ( x < (y << 1)) {
            break;
        }
        if (s == 63) {
            break;
        }
    }

    unsigned long long div = 0UL;
    for( ; s >= 0; s--) {
        if (x >= y && x != 0) { // x > y 뿐만 아닌, x = y && x !=0 조건은 x와 y가 같은 경우를 위함
            div += (1UL << s);
            x -= y;             // 이진수의 나눗셈은 빼기가 된다. 이진수 이므로 한번만 뺄 수 있다.
        }
        y >>= 1;
    }

    struct div_rslt rslt;
    rslt.div = div;
    rslt.rest = x;
    return rslt;
}

bool test_div(unsigned long long x, unsigned long long y) {
    struct div_rslt rslt = bitop_div_u64(x, y);
 
    bool test_success = false;
    if (rslt.div != (x/y) || rslt.rest != (x%y)) {
        test_success = false;
    } else {
        test_success = true;
    }
    cout << (test_success? "[success] " : "[failure] ");
    cout << x << " / " <<  y << " = ";
    cout << rslt.div << "(" << rslt.rest << ")" << endl;
    return test_success;
}

void test_div_with_bit_op() {

    cout << " * " << __func__ << endl;
    test_div(11, 2);
    test_div(2, 11);
    test_div(1, 1);
    test_div(0xf, 1);
    test_div(0xffUL, 1);
    test_div(0xffffUL, 1);
    test_div(0xffffffUL, 1);
    test_div(0xffffffffUL, 1);
    test_div(0xffffffffffffffffUL, 1);
    test_div(1, 0xffffffffffffffffUL);
    test_div(0xffffffffffffffffUL, 0xffffffffffffffffUL);
}
