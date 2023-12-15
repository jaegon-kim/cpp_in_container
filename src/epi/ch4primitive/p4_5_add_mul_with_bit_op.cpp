#include <iostream>
#include <bitset>

using namespace std;

// ^(XOR)를 이용하여 덧셈을 수행하는 방법
unsigned long long bitop_add_u64(unsigned long long a, unsigned long long b) {
    unsigned long long carry = 0UL;
    while(b) {
        carry = a & b;   // carry를 수행할 값을 계산한다. '&' 하면 carry가 발생할 값이 나온다.
        a = a ^ b;       // carry가 발생하지 않을 값을 계산한다.
        b = carry << 1;  // carry를 실제 값으로 증가시킨다.
    }                    // a(carry가 발생하지 않을 값)과 b(carry를 실제 값으로 증가 시킨 값)에 대해서 다시 carry가 발생하는지 반복한다.
                         // carry가 더이상 발생하지 않으면 종료한다.
    return a;
}

// a * b 일 때, b를 a번으로 반복 덧셈하여 곱셈을 수행하는 방법을 다음 과 같이 좀더 효과적으로 할 수 있음
// 6 (0b110) * 3 (0b11) = 0b11 << 2 + 0b11 << 1

unsigned long long bitop_mul_u64(unsigned long long a, unsigned long long b) {
    unsigned long long sum = 0;
    while(a) {
        if (a & 0x1) {
            sum = bitop_add_u64(sum, b);
        }
        a >>= 1;
        b <<= 1;
    }
    return sum;
}

void test_add_mul_with_bit_op() {
    cout << " * " << __func__ << endl;
    cout << "15 + 13 = " <<  bitop_add_u64(15UL, 13UL) << endl;
    cout << "45 + 43 = " <<  bitop_add_u64(45UL, 43UL) << endl;
    cout << "102400 + 3500000111111 = " <<  bitop_add_u64(102400UL, 3500000111111UL) << endl;
    cout << "15 x 13 = " <<  bitop_mul_u64(15UL, 13UL) << endl;
    cout << "45 x 43 = " <<  bitop_mul_u64(45UL, 43UL) << endl;
    cout << "102400 x 3500000111111 = " <<  bitop_mul_u64(102400UL, 3500000111111UL) << endl; // 358,400,011,377,766,400

}
