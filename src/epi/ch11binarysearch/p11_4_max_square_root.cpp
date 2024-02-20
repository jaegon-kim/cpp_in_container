#include <iostream>
#include "utility/dump.hpp"

using namespace std;

namespace p11_4 {

    int find_max_sqaure_root(const int v) {
        int s = 1;
        int e = v;

        while( s < e ) {
            int m = (s + e) / 2;
            int m_square = m * m;
            if (m_square == v) {
                return m;
            } else if ( m_square < v) {
                s = m + 1; 
            } else {
                e = m - 1;
            }
        }

        return s;
    }

    void test(const int v) {
        int r = find_max_sqaure_root(v);
        cout << "max square root for " << v << " is " << r << endl;
    }
}

void test_p11_4_max_square_root() {
    PRINT_FUNC_NAME;
    p11_4::test(16);
    p11_4::test(300);
}
