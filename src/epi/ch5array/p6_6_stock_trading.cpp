#include <iostream>
#include <vector>

using namespace std;

struct trade {
    int b = 0;
    int s = 0;
};

trade trade_bf(const vector<int> & v) {

    trade t = {0, 0}; 
    size_t len = v.size();
    int p = 0x80000000;
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if ((v[j] - v[i]) > p) {
                t.b = i, t.s = j;
                p = v[j] - v[i];
            }
        }
    }
    return t;
}

trade trade_o_n(const vector<int> & v) {
    trade t = {0, 0};

    int len = v.size();
    if (len <= 1) {
        return t;
    }
    int max_p = 0; // 최고 수익
    int m = 0;     // 이전 시점의 최 저가
    for (int i = 0; i < len; i++) {

        // i 시점에서 최고 수익은 'v[i] - (i 이전의 최소 가격)' 일것이다. 
        // (i 이전의 최소 가격)' 은
        //  1) 다음과 같이 매번 루프로 계산하는 것도 가능하고
        //m = i;
        //for (int j = i; j >= 0; j--) {
        //    if (v[j] < v[m]) {
        //        m = j;
        //    }
        //}
        //  2) 다음과 같이 min(v[i], old_min)으로 계산하는 것도 가능하다.   
        if (v[m] > v[i]) {
            m = i;
        }

        if ((v[i] - v[m]) > max_p) {
            t.s = i;
            t.b = m;
            max_p = v[i] - v[m];
        }
    }

    return t;
}

void test(const vector<int> & v) {
    trade t;
    t = trade_bf(v);
    
    cout << "bf  : " << v[t.s] << " - " << v[t.b] << " = " << (v[t.s] - v[t.b]) << endl;
    t = trade_o_n(v);
    cout << "O(n): " << v[t.s] << " - " << v[t.b] << " = " << (v[t.s] - v[t.b]) << endl;
}

void test_stock_trading() {
    cout << " * " << __func__ << endl;
    cout << (int) (0x80000000) << endl; 

    test(vector<int>{310, 315, 275, 295, 260, 270, 290, 230, 255, 250});
    test(vector<int>{310, 310, 275, 275, 260, 260, 230, 230, 230});

}
