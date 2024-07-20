#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;

// 2xn tiling: https://www.acmicpc.net/problem/11726
//             (https://blog.naver.com/ndb796/221233586932)

#define MAX_N 1024
namespace a03_02 {

    int tiling(int n, int cache[]) {
        if (n == 1) {
            return 1;
        }
        if (n == 2) {
            return 3;
        }
        if (cache[n]) {
            return cache[n];
        }
        cache[n] = tiling(n - 1, cache) + tiling(n - 2, cache) + tiling(n - 2, cache);
        return cache[n];
    }

    int cache[MAX_N];

    void test(int n) {
        memset(cache, 0, sizeof(cache));        
        int c = tiling(n, cache);
        cout << c << endl;
    }
}

void test_a03_02_2xN_3tile_tiling() {
    PRINT_FUNC_NAME;
    a03_02::test(2);
    a03_02::test(8);    
    a03_02::test(12);    

}