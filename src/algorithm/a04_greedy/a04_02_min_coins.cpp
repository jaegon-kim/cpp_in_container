#include <iostream>
#include <utility/dump.hpp>

using namespace std;

namespace a04_02 {
    int coins[] = {100, 50, 25, 10, 5, 1}; // 동전의 종류

    // 동전의 종류가 주어졌을 때, 최소 개수의 동전을 사용해서 cents를 구성하는 문제
    int min_coin(int cents) {
        int cnt = 0;
        for (auto coin :coins) {
            cnt += (cents / coin);
            cents %= coin;
        }

        return cnt;
    }

    void test() {
        cout << min_coin(200) << endl;
        cout << min_coin(48) << endl;

    }

}

void test_a04_02_min_coins() {
    PRINT_FUNC_NAME;
    a04_02::test();
}