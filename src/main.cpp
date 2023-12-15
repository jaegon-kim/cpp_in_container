#include <iostream>

#include <main.hpp>
#include <utility/util.hpp>

extern void test_p4_1_parity();
extern void test_p4_2_bit_swap();
extern void test_p4_3_bit_reverse();
extern void test_closed_same_bit_cnt_num();
extern void test_add_mul_with_bit_op();
extern void test_div_with_bit_op();

int main() {

    std::cout << bracketStr(helloWorld) << std::endl;

    //test_p4_1_parity();
    //test_p4_2_bit_swap();
    //test_p4_3_bit_reverse();
    //test_closed_same_bit_cnt_num();
    //test_add_mul_with_bit_op();
    test_div_with_bit_op();

    return 0;
}