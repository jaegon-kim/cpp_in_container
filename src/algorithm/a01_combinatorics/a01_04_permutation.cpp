#include <iostream>
#include <list>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace a01_04 {

    int permutation(list<int> & l, size_t s, vector<int> & p) {

        if (!s) {
            dump_vec(p, true);
            return 1;
        }

        int cnt = 0;
        for (size_t i = 0; i < s; i++) {
            int v = l.front();
            l.pop_front();
            p.push_back(v);

            cnt += permutation(l, s - 1, p);

            p.pop_back();
            l.push_back(v);
        }

        return cnt;
    }

    void test(int n) {
        list<int> l;
        for (int i = 1 ; i <= n; i++) {
            l.push_back(i);
        }

        vector<int> p;
        int r = permutation(l, (size_t) n, p);
        cout << "number of permutation: " <<  r << endl;
    }
}

void test_a01_04_permutation() {
    PRINT_FUNC_NAME;
    a01_04::test(2);
    a01_04::test(3);
    a01_04::test(4);

}
