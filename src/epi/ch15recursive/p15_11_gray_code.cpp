#include <iostream>
#include <vector>
#include "utility/dump.hpp"
#include <bitset>

using namespace std;

namespace p15_11 {

    vector<int> gray_code(int n) {
        vector<int> v_gc;
        if (n == 1) {
            v_gc.push_back(0);
            v_gc.push_back(1);
            return v_gc;
        }

        v_gc = gray_code(n - 1);
        size_t len = v_gc.size();
        int a = 1 << (n - 1);
        for (int i = len - 1; i >= 0 ; i--) {
            v_gc.push_back(v_gc[i] | a);
        }
        return v_gc;
    }

    void test(int n) {
        vector<int> r = gray_code(n);
        for (int a: r) {
            cout << bitset<8>(a) << "(" << a << "),";
        }
        cout << endl;
    }

    // Gracode encoding - https://woodforest.tistory.com/147
    template <typename T>
    T binary2gray(T v) {
        T mask = (T) (~(1UL << (sizeof(v) * 8 - 1)));
        T s = ((v & mask) >> 1);
        //cout << "mask: " << bitset<8>(mask) << " - v: " << bitset<8>(v) << " - s: " <<  bitset<8>(s) << endl;
        return (v  ^ s);
    }

    template <typename T>
    T gray2binary(T v) {
        size_t bitlen = sizeof(v) * 8;
        T mask = 1 << (bitlen - 1);
        T b = v & mask;
        for (size_t i = 0; i < (bitlen - 1); i++) {
            T x = (v & (mask >> 1)) ^ ((b & mask) >> 1) ;
            b |= x;
            mask = mask >> 1;
        }
        return b;
    }

    void test_gray() {
        cout << "gray code mapping" << endl;
        //for (unsigned int i = 0; i <= 0xff; i++) {
        for (unsigned int i = 129; i <= 129; i++) {
            unsigned char g_code = binary2gray<unsigned char>(i);
            unsigned char b_code = gray2binary<unsigned char>(g_code);
            cout << "(" << i << ") " << bitset<8>(i) << "-" << bitset<8>(g_code) << "-" << bitset<8>(b_code);
            if ((unsigned char)i == b_code) {
                cout << endl;
            } else {
                cout << " failure" << endl;
            }
        }
        //binary2gray<unsigned short>(1);

    }

}

void test_p15_11_gray_code() {
    PRINT_FUNC_NAME;
    p15_11::test(2);
    p15_11::test(3);
    p15_11::test(4);
    // gray code는 4bit 까지만 쓸 수 있는 것인지 ?
    //p15_11::test_gray();


}

