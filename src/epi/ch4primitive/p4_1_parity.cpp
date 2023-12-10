
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

// EPI p38
int parity_o_k(unsigned long long n) {

    unsigned long long parity = 0;
    while (n) {
        parity ^= 1;
        n &= (n - 1); // It removes last '1' bit
    } 
    return (int) parity;
}

int parity16_o_k(unsigned short n) {

    unsigned short parity = 0;
    while (n) {
        parity ^= 1;
        n &= (n - 1); // It removes last '1' bit
    } 
    return (int) parity;
}

int map[65536];

void init_map() {
    for (unsigned int i = 0; i < 65536; i++) {
        map[i] = parity16_o_k((short)i);
    }
}

// EPI p39
int parity_o_4(unsigned long long n) {

    int parity = map[ n & 0xffffUL];
    parity ^= map [(n & 0xffff0000UL) >> 16];
    parity ^= map [(n & 0xffff00000000UL) >> 32];
    parity ^= map [(n & 0xffff00000000UL) >> 48];

    return parity;
}

// EPI p40
int parity_o_log_n(unsigned long long n) {
    unsigned long long parity = n;
    parity = (parity & 0xffffffffUL) ^ (parity >> 32);
    parity = (parity & 0xffffUL) ^ (parity >> 16);
    parity = (parity & 0xffUL) ^ (parity >> 8);
    parity = (parity & 0xfUL) ^ (parity >> 4);
    parity = (parity & 0x3UL) ^ (parity >> 2);
    parity = (parity & 0x1UL) ^ (parity >> 1);
    return parity;
}


void test_count_bit() {

    init_map();

    std::cout << count_bit(3);
    std::cout << "(" << parity_o_n(3) << "), ";
    std::cout << "(" << parity_o_k(3) << "), ";
    std::cout << "(" << parity_o_4(3) << "), ";
    std::cout << "(" << parity_o_log_n(3) << "), ";
    std::cout << std::endl;

    std::cout << count_bit(0b010101); // binary literal
    std::cout << "(" << parity_o_n(0b010101) << "), "; // binary literal
    std::cout << "(" << parity_o_k(0b010101) << "), "; // binary literal
    std::cout << "(" << parity_o_4(0b010101) << "), ";
    std::cout << "(" << parity_o_log_n(0b010101) << "), ";
    std::cout << std::endl;

    std::cout << count_bit(0b111100001111);
    std::cout << "(" << parity_o_n(0b111100001111) << "), ";
    std::cout << "(" << parity_o_k(0b111100001111) << "), ";
    std::cout << "(" << parity_o_4(0b111100001111) << "), ";
    std::cout << "(" << parity_o_log_n(0b111100001111) << "), ";
    std::cout << std::endl;

    std::cout << count_bit(0b111111111110);
    std::cout << "(" << parity_o_n(0b111111111110) << "), ";
    std::cout << "(" << parity_o_k(0b111111111110) << "), ";
    std::cout << "(" << parity_o_4(0b111111111110) << "), ";
    std::cout << "(" << parity_o_log_n(0b111111111110) << "), ";
    std::cout << std::endl;

    std::cout << count_bit(0b111111111111);
    std::cout << "(" << parity_o_n(0b111111111111) << "), ";
    std::cout << "(" << parity_o_k(0b111111111111) << "), ";
    std::cout << "(" << parity_o_4(0b111111111111) << "), " ;
    std::cout << "(" << parity_o_log_n(0b111111111111) << ")," ;
    std::cout << std::endl;

}


void test_p4_1_parity() {
    std::cout << "test parity" << std::endl;
    test_count_bit();
    test_xor();
}