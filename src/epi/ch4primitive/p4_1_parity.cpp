
#include <iostream>

int count_bit(long n) {
    long num_bit = 0;
    while(n) {
        num_bit += (n & 1);
        n >>= 1;
    }
    return num_bit;
}

void test_count_bit() {
    std::cout << count_bit(3) << std::endl;
    std::cout << count_bit(0b010101) << std::endl; // binary literal
    std::cout << count_bit(0b111100001111) << std::endl;

}

void test_p4_1_parity() {
    std::cout << "test parity" << std::endl;
    test_count_bit();
}