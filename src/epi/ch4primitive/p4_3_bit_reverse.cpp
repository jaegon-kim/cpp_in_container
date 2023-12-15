#include <iostream>
#include <bitset>

using namespace std;

namespace p4_3 {

    unsigned short bit_swap_u16(unsigned short a, int i, int j) {
        if (((a >> i) & 0x1) != ((a >> j) & 0x1)) {
            a ^= ((0x1 << i) | (0x1 << j));
        }
        return a;
    }

    unsigned short bit_reverse_u16(unsigned short a) {
        for (int i = 0; i < 8; i++) {
            a = bit_swap_u16(a, i, 15 - i);
        }
        return a;
    }

    unsigned short map[65536];

    void init_map() {
        for (int i = 0 ; i < 65536; i++) {
            map[i] = bit_reverse_u16(i);
            //cout << bitset<16>(i) << ": " << bitset<16>(map[i]) << endl;
        }
    }

    unsigned long long bit_reverse_u64(unsigned long long a) {
        return ((unsigned long long) map[(a >> 48) & 0xffff]) |
            ((unsigned long long)(map[(a >> 32) & 0xffff]) << 16) |
            ((unsigned long long)(map[(a >> 16) & 0xffff]) << 32) |
            ((unsigned long long)(map[(a      ) & 0xffff]) << 48);
    }

}

void test_p4_3_bit_reverse() {
    cout << "* " << __func__ << endl;
    p4_3::init_map();
    for (int i = 0; i < 100; i++) {
        unsigned long long v = 0b1000000011000000111000001111000000000000000000000000000000000000;
        cout << bitset<64>(i + v) << ": " << bitset<64>(p4_3::bit_reverse_u64(i + v)) << endl;
    }

}

