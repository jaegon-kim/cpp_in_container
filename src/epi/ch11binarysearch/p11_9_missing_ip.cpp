#include <iostream>
#include "utility/dump.hpp"

#include <vector>
#include <unordered_map>

using namespace std;

#define UPPER16 65536
#define BITMAP_ENTRY_SIZE (sizeof(unsigned long long))
#define BITMAP_SIZE (UPPER16/BITMAP_ENTRY_SIZE)

namespace p11_9 {

    unsigned int g_ip = 0;

    static inline unsigned int get_ip() {

        ++g_ip;

        while(true) {
            switch(g_ip) {
                case 0x00010001:
                case 0x00020101:
                case 0x00020102:
                case 0x00020103:
                case 0x00030105:
                case 0x00030107:
                    ++g_ip;
                    break;
                default:
                    return g_ip;
            }
        }
    }

    template <typename T>
    static inline void init_arr(T arr[], size_t len, T v) {
        for(size_t i = 0; i < len; i++) {
            arr[i] = v;
        }
    }

    template <typename T>
    static inline void init_vec(vector<T> & vec, size_t len, T v) {
        for(size_t i = 0; i < len; i++) {
            vec[i] = v;
        }
    }


    static inline void set_bitmap(vector<unsigned long long> & bitmap, size_t i) {
        size_t idx = i / BITMAP_ENTRY_SIZE;
        size_t shift = i % BITMAP_ENTRY_SIZE;
        bitmap[idx] |= (0x1UL << shift );
    }

    static inline bool get_bitmap(vector<unsigned long long> & bitmap, size_t i) {
        size_t idx = i / BITMAP_ENTRY_SIZE;
        size_t shift = i % BITMAP_ENTRY_SIZE;
        return bitmap[idx] & (0x1UL << shift );
    }

    void missing_ips() {
        int upper16_counter[UPPER16];
        init_arr<int>(upper16_counter, UPPER16, 0);
        vector<unsigned long long> bitmap(BITMAP_SIZE);

        unsigned int ip = 0;
        while((ip = get_ip())) {
            upper16_counter[ip >> 16]++;
        }

        for (size_t i = 1; i < UPPER16; i++) {
            init_vec<unsigned long long>(bitmap, BITMAP_SIZE, 0UL);

            if (upper16_counter[i] != UPPER16) {
                printf("%04lx: size: %d\n", i, upper16_counter[i]);

                while((ip = get_ip())) {
                    if ((ip >> 16) == i) {
                        set_bitmap(bitmap, ip & 0x0000FFFF);
                    }
                }

                for(size_t j = 0; j < 65536; j++) {
                    if (!get_bitmap(bitmap, j)) {
                        printf("  %04lx %04lx\n", i, j);
                    }
                }
            }
        }
    }

    void missing_ips_map() {
        int upper16_counter[UPPER16];
        init_arr<int>(upper16_counter, UPPER16, 0);

        unsigned int ip = 0;
        cout << "ip store loading start" << endl;
        while((ip = get_ip())) {
            upper16_counter[ip >> 16]++;
        }
        cout << "ip store loading completed" << endl;

        unordered_map<unsigned long long, vector<unsigned long long>> map;

        for (size_t i = 0; i < UPPER16; i++) {
            if (upper16_counter[i] != UPPER16) {
                //printf("%04lx: size: %d\n", i, upper16_counter[i]);
                //map[i] = vector<unsigned long long>(BITMAP_SIZE);
                map.emplace(i, vector<unsigned long long>(BITMAP_SIZE));
            }
        }

        cout << "ip store loading start" << endl;
        while((ip = get_ip())) {
            unsigned long long k = ip >> 16;

            if (upper16_counter[k] != UPPER16) {
                set_bitmap(map[k], ip & 0x0000FFFF);
            }
        }
        cout << "ip store loading completed" << endl;

        cout << "Not existing ip list: " << endl;
        for (auto p: map) {
            for(size_t j = 0; j < 65536; j++) {
                if (!get_bitmap(p.second, j)) {
                    printf("  0x%04llx %04lx\n", p.first, j);
                }
            }
        }

    }


    void test_bitmap() {
        vector<unsigned long long> bitmap(BITMAP_SIZE);;
        init_vec<unsigned long long>(bitmap, BITMAP_SIZE, 0UL);

        set_bitmap(bitmap, 0);
        set_bitmap(bitmap, 1);
        set_bitmap(bitmap, 100);
        set_bitmap(bitmap, 65535);
        for(size_t j = 0; j < 65536; j++) {
            if (get_bitmap(bitmap, j)) {
                printf("  0x%04lx(%lu)\n", j, j);
            }
        }
    }

    void test() {
      //missing_ips();
      missing_ips_map();  
      //test_bitmap();
    }
}

void test_p11_9_missing_ip() {
    PRINT_FUNC_NAME;
    p11_9::test();
}