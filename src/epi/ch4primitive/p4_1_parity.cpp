
#include <iostream>

// EPI p35
int count_bit(unsigned int n) {
    long num_bit = 0;
    while(n) {
        num_bit += (n & 1);
        n >>= 1;
    }
    return num_bit;
}

void test_xor() {
    std::cout << "1 ^ 1 = " << (1 ^ 1) << std::endl;
    std::cout << "1 ^ 0 = " << (1 ^ 0) << std::endl;
    std::cout << "0 ^ 1 = " << (0 ^ 1) << std::endl;
    std::cout << "0 ^ 0 = " << (0 ^ 0) << std::endl;
}

// EPI p38
int parity_o_n(unsigned long long n) {

    unsigned long long parity = 0;
    while (n) {
        parity ^= (n & 1);
            // 1 ^ Odd(1) = Even(0)
            // 0 ^ Odd(1) = Odd(1)
            // 1 ^ Even(0) = Odd(1)
            // 0 ^ Even(0) = Even(0)

        n >>= 1;
    } 
    return (int) parity;
}

void test_count_bit() {
    std::cout << count_bit(3);
    std::cout << "(" << parity_o_n(3) << ")" << std::endl;

    std::cout << count_bit(0b010101); // binary literal
    std::cout << "(" << parity_o_n(0b010101) << ")" << std::endl; // binary literal

    std::cout << count_bit(0b111100001111);
    std::cout << "(" << parity_o_n(0b111100001111) << ")" << std::endl;

    std::cout << count_bit(0b111111111110);
    std::cout << "(" << parity_o_n(0b111111111110) << ")" << std::endl;

    std::cout << count_bit(0b111111111111);
    std::cout << "(" << parity_o_n(0b111111111111) << ")" << std::endl;

}


void test_p4_1_parity() {
    std::cout << "test parity" << std::endl;
    test_count_bit();
    test_xor();
}