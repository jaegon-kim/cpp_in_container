#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

/*
    * recursive example (지수는 2진수 표기임)
    Goal: pow(2, 1011)
    1) 2^1011 = 2^1 * 2^1010
       2^1010 = 2^101 * 2^101   (101 + 101 == 101 * 2 == 101 << 1)
    2) 2^101  = 2^1 * 2^100
       2^100  = 2^10 * 2^10     (10 + 10 == 10 * 2 == 10 << 1)
    3) 2^10   = 2^1 * 2^1
*/

double pow_double_recurs(double x, int y) {

    double pow = 1.0;
    if (y & 0x1) {
        pow *= x;
    }
    y >>= 1;

    if (y == 0) {
        return pow;
    }

    double ret = pow_double_recurs(x, y);
    return pow * ret * ret;
}

/*
   * Loop example
    Goal: pow(2, 1011)
    -------------------------------------------------
     2^1011  =  2^0001  +  2^0010  +  2^0000  + 2^1000   
    -------------------------------------------------
        2^1
        2^10 = 2^1 * 2^1
        2^100 = 2^10 * 2^10
        2^1000 = 2^100 * 2^100
    -------------------------------------------------
    1) 지수의 LSB 부터 합산 여부를 계산한다.
    2) 동시에 지수의 <<1 에 따른 값 증가를 계산한다.
*/

double pow_double_loop(double x, int y) {
    double result = 1.0;

    while(y) {
        if (y & 0x1) {
            result *= x;
        }
        x *= x; // example 2^100 = 2^10 * 2^10
        y >>= 1;
    }

    return result;
}

bool test_pow(double x, int y) {

    if (y < 0) {
        x = 1.0/x;
        y = -y;
    }
    //double r = pow_double_recurs(x, y);
    double rslt = pow_double_loop(x, y);

    bool success = (rslt == pow(x, y));
    cout << "[" << (success? "success": "failure") << "] " << x << " ^ " << y << " = " << rslt << endl;
    return success;
}

void test_pow_bit_op() {
    cout << " * " << __func__ << endl;

    for (int i = 0 ; i < 10; i++) {
        for (int j = 0 ; j < 10; j++) {
            test_pow(i, j);
        }
    }

}