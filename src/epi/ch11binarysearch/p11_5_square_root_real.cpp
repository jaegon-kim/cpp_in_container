#include <iostream>
#include "utility/dump.hpp"
#include <limits>
#include <cmath> // std::abs(double)
#include <algorithm> // std::max




using namespace std;

namespace p11_5 {

    // numeric_limits<double>::epsilon() : (입실론) double 형이 가질 수 있는 최대 오차 값이다.
    // cout << "maximun error value of double: " <<  numeric_limits<double>::epsilon() << endl;
    // 하지만 그냥 차이(a-b)를 입실론과 비교하는 것이 아니라, 
    // 가장 큰 수의 절대값으로 차이를 나누어 데이터의 범위를 [-1, 1 ]으로 조절하여 비교한다. (정규화)
    // a = 1000, b = 999 인 값의 차분과, a = 1e-5, b = 9e-6의 차분 값 비교할 수 있도록 정규화 한다.
    // epsilson 값을 쓰려면 정규화가 필요한 것일까 ? 

    int compare(double a, double b) {
        double reg_diff = (a - b) / max(abs(a), abs(a));
        if (reg_diff < -numeric_limits<double>::epsilon()) {
            return -1;
        } else if (reg_diff > numeric_limits<double>::epsilon()) {
            return 1;
        } else {
            return 0;
        }
    }

    double square_root_real(double r) {

        if (r < 0.0) {
            cout << "not supported real " << r << endl;
            return 0.0;
        } 

        if (!compare(r, 1.0)) {
            return 1.0;
        }

        double s = 1.0;
        double e = r;
        double m = 0.0;

        while(compare(s, e) < 0) { // s < e
            m = s + (e - s) / 2.0;
            double square = m * m;

            int c = compare(square, r);
            if (!c) { // square == r
                return m;
            } else if (c < 0) { // sqaure < r
                s = m;
            } else { // r < square
                e = m;
            }
        }
        return m;
    }

    void test(double r) {
        double sr = square_root_real(r);
        cout << "sqrt(r): " << sqrt(r) << ", square_root_real(r): " << sr << endl;
    }

}

void test_p11_5_square_root_real() {
    PRINT_FUNC_NAME;

    cout << "epsilon of double: " << numeric_limits<double>::epsilon() << endl;  

    cout << p11_5::compare(0.1, 0.1) << endl;
    cout << p11_5::compare(0.2, 0.1) << endl;
    cout << p11_5::compare(0.1, 0.2) << endl;

    cout << p11_5::compare(1e-5, 1e-5) << endl;
    cout << p11_5::compare(1e-5, 9e-6) << endl;
    cout << p11_5::compare(9e-6, 1e-5) << endl;

    p11_5::test(1);
    p11_5::test(4);
    p11_5::test(5);
    p11_5::test(9);
    p11_5::test(25);
    p11_5::test(27);
    p11_5::test(85.4);

    p11_5::test(exp(1.0));
    p11_5::test(exp(2.0));

}