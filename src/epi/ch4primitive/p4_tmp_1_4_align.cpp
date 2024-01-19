#include <iostream>

#include "utility/dump.hpp"

using namespace std;

// 0 -> align4: 0, align8: 0
// 1 -> align4: 4, align8: 8
// 2 -> align4: 4, align8: 8
// 3 -> align4: 4, align8: 8
// 4 -> align4: 4, align8: 8
// 5 -> align4: 8, align8: 8
// 6 -> align4: 8, align8: 8
// 7 -> align4: 8, align8: 8
// 8 -> align4: 8, align8: 8
// 9 -> align4: 12, align8: 16
// 10 -> align4: 12, align8: 16
// 11 -> align4: 12, align8: 16
// 12 -> align4: 12, align8: 16
// 13 -> align4: 16, align8: 16
// 14 -> align4: 16, align8: 16
// 15 -> align4: 16, align8: 16
// 16 -> align4: 16, align8: 16
// 17 -> align4: 20, align8: 24
// 18 -> align4: 20, align8: 24
// 19 -> align4: 20, align8: 24
// 20 -> align4: 20, align8: 24
// 21 -> align4: 24, align8: 24
// 22 -> align4: 24, align8: 24
// 23 -> align4: 24, align8: 24
// 24 -> align4: 24, align8: 24
// 25 -> align4: 28, align8: 32
// 26 -> align4: 28, align8: 32
// 27 -> align4: 28, align8: 32
// 28 -> align4: 28, align8: 32
// 29 -> align4: 32, align8: 32


// v & 0b11(3) 에 값이 있으면 + 3(0b11)이 carry를 만든다.
size_t align4(size_t v) {
    return (v + 3) & 0xfffffffffffffffcUL;
}

// v & 0b111(7) 에 값이 있으면 + 7(0b111)이 carry를 만든다.
size_t align8(size_t v) {
    return (v + 7) & 0xfffffffffffffff8UL;
}

void test_p4_tmp_1_4_align() {
    PRINT_FUNC_NAME;

    for (size_t i = 0; i < 30; i++) {
        cout << i << " -> align4: " << align4(i) << ", align8: " << align8(i) << endl;
    }
}