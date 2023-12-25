#include <iostream>
#include <vector>
#include <utility>

using namespace std;

namespace p5_7 {

    struct trade {
        int b = 0;
        int s = 0;
    };

    trade trade_o_n(const vector<int> & v) {
        trade t = {0, 0};
        int len = v.size();

        int min_b = 0;
        int max_p = 0;
        for (int i = 0; i < len; i++) {
            if (v[i] < v[min_b]) {
                min_b = i;
            }

            if ((v[i] - v[min_b]) > max_p) {
                max_p = v[i] - v[min_b];
                t.b = min_b;
                t.s = i;
            }
        }

        return t;
    }

    void dump(const vector<int> & v, bool nl) {
        cout << "{";
        size_t len = v.size();
        for (size_t i = 0; i < len; i++) {
            cout << v[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void dump_trade(const trade & t, const vector<int> & v) {
        cout << v[t.s] << "-" << v[t.b] << "=" << (v[t.s] - v[t.b]);
    }

    pair<trade, trade> trade_twice_02(const vector<int> & v) {

        int len = v.size();
        //dump(v, true);
        int max_p = 0;
        trade max_t1 = {0, 0};
        trade max_t2 = {0, 0};

        for (int i = 1; i < len; i++) {
            vector<int> v1(v.begin(), v.begin() + i);
            vector<int> v2(v.begin() + i, v.begin() + len);
            //dump(v1, false);
            //dump(v2, true);
            trade t1 = trade_o_n(v1);
            int p1 = v1[t1.s] - v1[t1.b];

            trade t2 = trade_o_n(v2);
            int p2 = v2[t2.s] - v2[t2.b];

                // cout << "  * ";
                // dump_trade(t1, v);
                // cout << ", ";
                // dump_trade(t2, v);
                // cout << endl;


            if ((p1 + p2) > max_p) {
                max_t1 = t1;
                max_t2.b = t2.b + i;
                max_t2.s = t2.s + i;
                max_p = (p1 + p2);
            }
        }
        

        return make_pair(max_t1, max_t2);
    }


    pair<trade, trade> trade_twice_o_n(const vector<int> & v) {

        //dump(v, true);

        int len = v.size();
        int max_p = 0;
        int min_b = 0;
        trade max_t = {0, 0};
        
        vector<trade> t1(len);
        for (int i = 0; i < len; i++ ) {

            if (v[i] < v[min_b]) {
                min_b = i;
            }

            if ((v[i] - v[min_b]) > max_p) {
                max_p = (v[i] - v[min_b]);
                max_t.b = min_b;
                max_t.s = i;
            }

            t1[i] = max_t;
        }
        /*
        for (int i = 0; i < len; i++) {
            cout << i << ")";
            dump_trade(t1[i], v);
            cout << ", ";
        }
        cout << endl;
        */

        int max_s = len - 1;
        max_p = 0;
        max_t = {len - 1, len - 1};
        vector<trade> t2(len);
        for (int i = (len - 1); i >= 0; i--) {
            if (v[i] > v[max_s]) {
                max_s = i;
            }

            if ((v[max_s] - v[i]) > max_p) {
                max_p = (v[max_s] - v[i]);
                max_t.b = i;
                max_t.s = max_s;
            }

            t2[i] = max_t;
        }

        /*
       for (int i = 0; i < len; i++) {
            cout << i << ")";
            dump_trade(t2[i], v);
            cout << ", ";
        }
        cout << endl;
        */

        max_p = 0;
        int max_i = 0;
        for (int i = 0; i < len; i++) {
            int p1 = v[t1[i].s] - v[t1[i].b];
            int p2 = v[t2[i].s] - v[t2[i].b];

            if ((p1 + p2) > max_p) {
                max_p = p1 + p2;
                max_i = i;
            }
        }

        return make_pair(t1[max_i], t2[max_i]);
    }


    void test_trade_twice(const vector<int> & v) {
       
        dump(v, true);
        pair<trade, trade> p  = trade_twice_02(v);
        cout <<"O(n^2): ";
        dump_trade(p.first, v);
        cout << ", ";
        dump_trade(p.second, v);
        cout << endl;

        p = trade_twice_o_n(v);
        cout <<"O(n):   ";
        dump_trade(p.first, v);
        cout << ", ";
        dump_trade(p.second, v);
        cout << endl;
    }
}

void test_p5_7_stock_trading_twice() {
    cout << " * " << __func__ << endl;

    p5_7::test_trade_twice(vector<int>{310, 315, 275, 295, 260, 270, 290, 230, 255, 250});
    p5_7::test_trade_twice(vector<int>{315, 275, 295, 260, 270, 290, 230, 255, 250});
    p5_7::test_trade_twice(vector<int>{310, 310, 275, 275, 260, 260, 230, 230, 230});
    p5_7::test_trade_twice(vector<int>{12, 11, 13, 9, 12, 8, 14, 13, 15});
}