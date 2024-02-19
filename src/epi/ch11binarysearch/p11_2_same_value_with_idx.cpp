#include <iostream>
#include "utility/dump.hpp"

using namespace std;

namespace p11_2 {

    // v는 1) 중복되 원소가 없고, 2) 정렬되어 있는 Vector이다.
    // v에서 index 값과 같은 값을 갖는 index를 찾는다. 
    //       0  1  2  3  4  5  6 
    // ex) {-2, 0, 2, 3, 6, 7, 9} --> 2 또는 3
    int find_same_value_with_idx(const vector<int> & v) {
        int s = 0;
        int e = v.size() - 1;
        
        while(s <= e) {
            int m = (s + e) / 2;
            if (m < v[m]) { // v[m]이 m 보다, 크므로, m보다 큰 영역에는 index 값과 같은 값을 v[m]이 갖지 못한다.
                e = m - 1;
            } else if (m == v[m]) {
                return m;
            } else { // m > v[m]이므로, m 보다 작은 영역에는 index 값과 같은 값을 v[m이 갖지 못한다.]
                s = m + 1;
            }
        }

        return -1;
    }

    void test(const vector<int> & v) {
        int r = find_same_value_with_idx(v);
        cout << r << endl;
    }
}

void test_p11_2_same_value_with_idx() {
    PRINT_FUNC_NAME;

    //                        0  1  2  3  4  5  6 
    p11_2::test(vector<int> {-2, 0, 2, 3, 6, 7, 9});
}