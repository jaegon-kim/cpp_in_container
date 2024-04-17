#include <iostream>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p15_01 {

    bool valid_order(vector<int> & p) {
        for(size_t i = 1; i < p.size(); i++) {
            if (p[i] >= p[i-1]) {
                return false;
            }
        }
        return true;
    }

    void check_order_all(vector<int> & from, vector<int> & to, vector<int> & tmp) {
        if(!valid_order(from)) {
            cout << "invalid order in from" << endl;
        }
        if(!valid_order(to)) {
            cout << "invalid order in to" << endl;
        }
        if(!valid_order(tmp)) {
            cout << "invalid order in tmp" << endl;
        }
    }

    void move(vector<int> & from, vector<int> & to, vector<int> & tmp, int depth) {

        if (depth == 1) {
            int v = from.back();
            from.pop_back();
            to.push_back(v);
            //check_order_all(from, to, tmp);
            return;
        }

        move(from, tmp, to, depth - 1);
        int v = from.back();
        from.pop_back();
        to.push_back(v);
        move(tmp, to, from, depth - 1);
        //check_order_all(from, to, tmp);
    }

    void test(int n) {
        vector<int> p1, p2, p3;
        for(int i = n; i > 0; i--) {
            p1.push_back(i);
        }
        cout << "p1: ";
        dump_vec(p1, true);
        cout << "p2: ";
        dump_vec(p2, true);
        cout << "p3: ";
        dump_vec(p3, true);
        move(p1, p2, p3, p1.size());
        cout << "--move(p1->p2)--" << endl;
        cout << "p1: ";
        dump_vec(p1, true);
        cout << "p2: ";
        dump_vec(p2, true);
        cout << "p3: ";
        dump_vec(p3, true);
    }
}


void test_p15_01_hanoi_tower() {
    PRINT_FUNC_NAME;
    p15_01::test(20);
}
