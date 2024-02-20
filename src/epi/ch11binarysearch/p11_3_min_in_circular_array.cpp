#include <iostream>
#include "utility/dump.hpp"
#include <vector>

using namespace std;

namespace p11_3 {

    // Circular Array에서 최소 값을 찾기
    int min_in_circular_array(const vector<int> & v) {

        int s = 0;
        int e = v.size() - 1;

        while(s < e) {
            int m = (s + e) / 2;
            //cout << "s: " << s << ", m: " << m << ", e: " << e << endl;
            if (v[m] > v[e]) { // 중간 값이 끝 값 보다 크면, 최소값은 오른쪽에 있을 것이다.
                s = m + 1;
            } else {  // 중간 값이 끝값보다 작으면, 최소값은 중간값을 포함한 왼쪽에 있을 것이다.
                e = m;
            }
            if (s == e) { //마지막 남는 것이 최소값이다.
                break;
            }
        }
        return s;
    }

    void test(const vector<int> & v) {
        int r = min_in_circular_array(v);
        cout << "r: " << r << endl;
    }
}

void test_p11_3_min_in_circular_array() {
    PRINT_FUNC_NAME;
    //                        0    1   2     3    4    5    6    7   8     9
    p11_3::test(vector<int> {103, 203, 220, 234, 279, 368, 378, 478, 550, 631});
    p11_3::test(vector<int> {631, 103, 203, 220, 234, 279, 368, 378, 478, 550});
    p11_3::test(vector<int> {550, 631, 103, 203, 220, 234, 279, 368, 378, 478});
    p11_3::test(vector<int> {478, 550, 631, 103, 203, 220, 234, 279, 368, 378});
    p11_3::test(vector<int> {378, 478, 550, 631, 103, 203, 220, 234, 279, 368});
    p11_3::test(vector<int> {368, 378, 478, 550, 631, 103, 203, 220, 234, 279});
    p11_3::test(vector<int> {279, 368, 378, 478, 550, 631, 103, 203, 220, 234});
    p11_3::test(vector<int> {234, 279, 368, 378, 478, 550, 631, 103, 203, 220});
    p11_3::test(vector<int> {220, 234, 279, 368, 378, 478, 550, 631, 103, 203});
    p11_3::test(vector<int> {203, 220, 234, 279, 368, 378, 478, 550, 631, 103});
}
