#include <iostream>

#include <main.hpp>
#include <utility/util.hpp>

extern void test_p4_1_parity();
extern void test_p4_2_bit_swap();
extern void test_p4_3_bit_reverse();
extern void test_closed_same_bit_cnt_num();
extern void test_add_mul_with_bit_op();
extern void test_div_with_bit_op();
extern void test_pow_bit_op();
extern void test_num_reverse();
extern void test_palindrom_num();
extern void test_p4_10_random_num_bit_op();
extern void test_p4_11_intersect_rec();

int main() {

    std::cout << bracketStr(helloWorld) << std::endl;

    //Chapter 4
    //test_p4_1_parity();
    //test_p4_2_bit_swap();
    //test_p4_3_bit_reverse();
    //test_closed_same_bit_cnt_num();
    //test_add_mul_with_bit_op();
    //test_div_with_bit_op();
    //test_pow_bit_op();
    //test_num_reverse();
    //test_palindrom_num();
    //test_p4_10_random_num_bit_op();
    test_p4_11_intersect_rec();

    return 0;
}