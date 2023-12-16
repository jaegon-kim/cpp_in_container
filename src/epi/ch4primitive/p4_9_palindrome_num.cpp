#include <iostream>
#include <cmath>

using namespace std;

bool is_palindrom_i32(int x) {
    if ( x < 0 ) {
        x *= -1;
    }

    if (x == 0) {
        return true;
    }
    int loc = log10(x);
    int b = pow(10, loc);
    //cout << "loc: " << loc << ", b: " << b << endl;
    if (b == 1) {
        return true;
    }

    while(x && b != 0) {
        // x / b  : 가장 높은 자리 수
        // x % 10 : 가장 낮은 자리 수 
        if ((x / b) != (x % 10)) {
            return false;
        }
        // x % b : 가장 높은 자리수를 제거 (212 % 100 = 12)
        // x /10 : 가장 낮은 자리수를 제거 (212 / 10 = 21)
        x = ((x % b) / 10);
        b /= 100;
    }
    return true;
}

bool test_palindrom_num(int x, bool expect) {
    bool rslt = is_palindrom_i32(x);
    bool success = (rslt == expect);
    cout << "[" << (success? "success": "failure") << "] " << x << ": is palindrom ? " << (rslt? "true": "false") << endl;
    return success;
}


void test_palindrom_num() {
    cout << " * " << __func__ << endl;

    // log10은 숫자의 자릿수를 계산하는 용도로 사용할 수 있다.
    cout << (int) log10(7) << endl;
    cout << (int) log10(1128) << endl;
    cout << (int) log10(19128) << endl;

    test_palindrom_num(0, true);
    test_palindrom_num(1, true);
    test_palindrom_num(7, true);
    test_palindrom_num(11, true);
    test_palindrom_num(121, true);
    test_palindrom_num(333, true);
    test_palindrom_num(2147447412, true);
    test_palindrom_num(234565432, true);
    test_palindrom_num(23455432, true);

    test_palindrom_num(12, false);
    test_palindrom_num(100, false);
    test_palindrom_num(2147483647, false);

}
