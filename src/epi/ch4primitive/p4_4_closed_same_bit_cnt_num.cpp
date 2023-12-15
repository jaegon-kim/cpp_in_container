#include <iostream>
#include <bitset>

using namespace std;

/*
 '1'bit의 개수가 같은 숫자 중에서 차분이 가장 적은 정수를 찾는 문제
  1) '1'bit의 개수가 같으려면, 이는 bit swap과 동일한다.
  2) bit 값이 다른 것을 swap 해야 한다.
  3) 차분이 가장 작으려면 a. 가장 낮은 위치에 있는, b. 인접한 bit를 교환해야 한다.
*/

unsigned long long find_closed_same_bit_cnt_num(unsigned long long a) {

    for (int i = 0 ; i < 63; i++) {
        if (((a >> i) & 0x1UL) != ((a >> (i+1)) & 0x1UL)) {
            cout << "(" << i << ") ";
            a ^= ((0x1UL << i) | (0x1UL << (i+1)));
            return a;
        }
    }

    return 0xffffffffffffffffUL;
} 

void test_closed_same_bit_cnt_num() {
    
    cout <<"10 : " << bitset<64>(find_closed_same_bit_cnt_num(0b10UL)) << endl; 
    cout <<"1 : " << bitset<64>(find_closed_same_bit_cnt_num(0b01UL)) << endl; 
    cout <<"110 : " << bitset<64>(find_closed_same_bit_cnt_num(0b110UL)) << endl; 
    cout <<"111 : " << bitset<64>(find_closed_same_bit_cnt_num(0b111UL)) << endl; 
    cout <<"1110 : " << bitset<64>(find_closed_same_bit_cnt_num(0b1110UL)) << endl; 

   cout <<"0b1000000000000000000000000000000000000000000000000000000000000000 : " 
        << bitset<64>(find_closed_same_bit_cnt_num(0b1000000000000000000000000000000000000000000000000000000000000000UL)) << endl; 

}