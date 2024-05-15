#include <iostream>
#include <list>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p16_04 {

    int subset(int c, int k, vector<int> & v, vector<int> & subset_v) {
        if (!k) {
            //dump_vec(subset_v, true);
            return 1;
        }

        int cnt = 0;
        for (int i = c + 1; i < (int) v.size(); i++) {
            subset_v.push_back(v[i]);
            cnt += subset(i, k - 1, v, subset_v);
            subset_v.pop_back();
        }

        return cnt;
    }

    size_t pascal_row(size_t n, size_t k) {
        if (n == k) {
            return 1;
        }

        if (k == 1) {
            return n;
        }

        return pascal_row(n - 1, k) + pascal_row(n - 1, k - 1);
    }

    void test(int n, int k) {
        vector<int> v;
        for (int i = 1; i <= n; i++) {
            v.push_back(i);
        }
        vector<int> subset_v;

        int r_s = subset(-1, k, v, subset_v);
        size_t r_p = pascal_row(n, k);

        cout << "n: " << n << ", k: " << k << ", # of subset: " <<  r_s << ", pascal's row: " << r_p << endl;
    }

    void test_pascal(int n, int k) {
        size_t r_p = pascal_row(n, k);
        cout << "n: " << n << ", k: " << k << ", pascal's row: " << r_p << endl;
    }


}

void test_p16_04_binomial_coefficient() {
    PRINT_FUNC_NAME;
    p16_04::test(4, 2);
    p16_04::test(4, 3);
    p16_04::test(5, 2);
    p16_04::test(5, 3);
    
    p16_04::test(100, 3);
    p16_04::test(200, 4);
    
    // recursion of subset takes too long time
    //p16_04::test(300, 5);

    // only pascal's row for binomial coefficent can be used for calculating the number of subset
    p16_04::test_pascal(300, 5);

}