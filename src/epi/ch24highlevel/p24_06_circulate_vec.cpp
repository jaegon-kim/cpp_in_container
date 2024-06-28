#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"
using namespace std;
namespace p24_06 {
    
    void circulate(vector<int> & v, vector<int> & c, size_t s) {
        size_t v_size = v.size();
        for (size_t i = 0; i < s; i++) {
            c[i] = v[v_size - s + i];
        }
        for (size_t i = 0; i < (v_size - s); i++) {
            v[v_size - i - 1] = v[v_size - i - 1 - s];
        }
        for (size_t i = 0; i < s; i++) {
            v[i] = c[i];
        }
    }

    void circulate_all(vector<int> & v, vector<int> & cache, size_t tot_count) {
        size_t cache_size = cache.size();
        size_t count;

        while(tot_count) {
            if (tot_count >= cache_size) {
                count = cache_size;
                tot_count -= cache_size;
            } else {
                count = tot_count % cache_size;
                tot_count = 0;
            }
            circulate(v, cache, count);
        }
    }

    void circulate_with_reverse(vector<int> & v, size_t tot_count) {
        tot_count = tot_count % v.size();
        reverse(v.begin(), v.end());
        //dump_vec(v, true);
        reverse(v.begin(), v.begin() + tot_count);
        //dump_vec(v, true);
        reverse(v.begin() + tot_count, v.end());
        //dump_vec(v, true);
    }

    void test(const vector<int> & i_v, size_t cache_size, size_t tot_count) {
        vector<int> v = i_v;
        vector<int> cache(cache_size);
        circulate_all(v, cache, tot_count);
        cout << "(" << cache_size << ", " << tot_count << ")  ";
        dump_vec(v, false);
        cout << " circulate with buffer" << endl;

        vector<int> v2 = i_v;
        circulate_with_reverse(v2, tot_count);
        cout << "        ";
        dump_vec(v2, false);
        cout << " circulate with reverse" << endl;
     }
}

void test_p24_06_circulate_vec() {
    PRINT_FUNC_NAME;
    p24_06::test(vector<int> {1, 2, 3, 4}, 1, 1);
    p24_06::test(vector<int> {1, 2, 3, 4}, 4, 1);

    p24_06::test(vector<int> {1, 2, 3, 4}, 2, 2);
    p24_06::test(vector<int> {1, 2, 3, 4}, 4, 2);

    p24_06::test(vector<int> {1, 2, 3, 4}, 3, 3);
    p24_06::test(vector<int> {1, 2, 3, 4}, 5, 3);

    p24_06::test(vector<int> {1, 2, 3, 4}, 1, 2);
    p24_06::test(vector<int> {1, 2, 3, 4}, 1, 3);

    p24_06::test(vector<int> {1, 2, 3, 4}, 2, 2);
    p24_06::test(vector<int> {1, 2, 3, 4}, 2, 3);
    p24_06::test(vector<int> {1, 2, 3, 4}, 2, 10);


}