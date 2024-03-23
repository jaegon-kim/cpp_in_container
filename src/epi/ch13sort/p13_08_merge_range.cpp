#include <iostream>
#include <vector>
#include <algorithm>
#include "utility/dump.hpp"

using namespace std;

namespace p13_08 {

    void dump(const vector<tuple<int, bool, int, bool>> & v, bool nl) {
        std::cout << "{";
        size_t len = v.size();
        for (size_t i = 0; i < len; i++) {
           std::cout << "(" 
                       << get<0>(v[i]) << ", " 
                       << (get<1>(v[i]) ? "closed" : "open")  << ", " 
                       << get<2>(v[i])  << ", " 
                       << (get<3>(v[i]) ? "closed" : "open")  
                    << "), ";
        }
        std::cout << "}";
        if (nl) {
            std::cout << std::endl;
        }
    }

    bool compare(const tuple<int, bool, int, bool> & a, const tuple<int, bool, int, bool> & b) {
        return get<0>(a) < get<0>(b);
    }

    vector<tuple<int, bool, int, bool>> merge(vector<tuple<int, bool, int, bool>> v) {
        sort(v.begin(), v.end(), compare);
        dump(v, true);

        vector<tuple<int, bool, int, bool>> m;

        tuple<int, bool, int, bool> ct = v[0];
        for (size_t i = 1; i < v.size(); i++) {
            if (get<2>(ct) < get<0>(v[i])) {
                m.push_back(ct);
                ct = v[i];
                continue;          
            }
            
            if (get<0>(ct) == get<0>(v[i])) {
                get<1>(ct) = get<1>(ct) || get<1>(v[i]);
            }

            if (get<2>(ct) > get<2>(v[i])) {
                // do nothing
            } else if (get<2>(ct) == get<2>(v[i])) {
                get<3>(ct) = get<3>(ct) || get<3>(v[i]);
            } else {
                get<2>(ct) = get<2>(v[i]);
                get<3>(ct) = get<3>(v[i]);
            }
        }
        m.push_back(ct);

        return m;
    }

    void test(const vector<tuple<int, bool, int, bool>> & v) {
        auto sv = merge(v);
        dump(sv,true);
    }
}

void test_p13_08_merge_range() {
    PRINT_FUNC_NAME;
    p13_08::test(vector<tuple<int, bool, int, bool>> {
        {2, true, 4, true}, {8, true, 11, false}, {13, false, 15, false}, {16, false, 17, false},
        {1, true, 1, true}, {3, true, 4, false}, {7, true, 8, false}, {12, false, 16, true},
        {0, false, 3, false}, {5, true, 7, false}, {9, false, 11, true}, {12, true, 14, true}
    });
}