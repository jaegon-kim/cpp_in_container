#include <iostream>
#include <bitset>

namespace p4_2 {
    // EPI p41
    unsigned int remove_last_1bit(unsigned int a) {
        return a & (a - 1);
    }

    unsigned int get_last_1bit(unsigned int a) {
        return a & ~(a - 1);
    }

    unsigned int reverse_bits(unsigned int a) {
        return a ^ (0xffffffff);
    }

    unsigned int swap_bit(unsigned int a, int i, int j) {
        if (((a >> i) & 0x1) != ((a >> j) & 0x1)) {
            return a ^ ((0x1 << i) | (0x1 << j));
        }
        return a;
    }


    void test_print_bitset() {
        unsigned int a = 0b01010100;
        std::cout << "original:         0b" << std::bitset<32>(a) << std::endl;
        std::cout << "remove last 1bit: 0b" << std::bitset<32>(remove_last_1bit(a)) << std::endl;
        std::cout << "get_last_1bit:    0b" << std::bitset<32>(get_last_1bit(a)) << std::endl;
        std::cout << "reverse bits:     0b" << std::bitset<32>(reverse_bits(a)) << std::endl;
        for (int i = 0 ; i < 16; i++) {
            a = swap_bit(a, i, 31 - i);
        }
        std::cout << "swap_bit:         0b" << std::bitset<32>(a) << std::endl;

    }
}

void test_p4_2_bit_swap() {
    std::cout << "* " << __func__ <<std::endl;
    p4_2::test_print_bitset();

}