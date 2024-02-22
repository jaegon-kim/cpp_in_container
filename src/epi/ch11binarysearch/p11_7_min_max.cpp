#include <iostream>
#include "utility/dump.hpp"

using namespace std;

namespace p11_7 {
    //return pair.first: min, pair.second: max
    pair<int, int> min_max(int a, int b) {
        if (a > b) {
            return make_pair(b, a);
        } else {
            return make_pair(a, b);
        }
    }

    pair<int, int> vec_min_max(const vector<int> & v) {
        if (v.size() == 1) {
            return make_pair(v[0], v[0]);
        }
        int min = v[0];
        int max = v[0];

        for(size_t i = 0; i < v.size(); i += 2) {
            //cout <<"(" << v[i] << ", " << v[i+1] << ")" << endl;
            pair<int, int> p = min_max(v[i], v[i+1]);

            max = min_max(max, p.second).second;
            min = min_max(min, p.first).first;
            
            if (i + 2 == v.size() - 1) {
                //cout <<"(" << v[i + 2] << ")" << endl;
                max = min_max(max, v[i + 2]).second;
                min = min_max(min, v[i + 2]).first;
                break;
            } 
        }
        return make_pair(min, max);
    }

    void test(const vector<int> & v) {
        pair<int, int> p = vec_min_max(v);
        cout << "min: " << p.first << ", max: " << p.second << " in ";
        dump_vec<int>(v, true);
    }
}


void test_p11_7_min_max() {
    PRINT_FUNC_NAME;
    p11_7::test(vector<int> {3});
    p11_7::test(vector<int> {3, 2});
    p11_7::test(vector<int> {3, 2, 5, 1, 2, 4});
    p11_7::test(vector<int> {3, 2, 5, 1, 2, 4, 3});
    p11_7::test(vector<int> {0, 0, 0, 0, 0, 0, 0});

}