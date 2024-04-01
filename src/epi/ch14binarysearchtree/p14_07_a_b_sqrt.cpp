#include <iostream>
#include <set>
#include <cmath>
#include <string>
#include <functional>


#include "utility/dump.hpp"

using namespace std;

namespace p14_07 {

    float value(const pair<int, int> & p) {
        return p.second * sqrt(2) + p.first;
    }

    string expr(const pair<int, int> & p) {
        return to_string(p.first) + "+" + to_string(p.second) +"*sqrt(2)";
    }

    vector<pair<int, int>> a_b_sqrt_with_set(size_t k) {

        auto compare = [](const pair<int, int> & a, const pair<int, int> & b) {
            return value(a) < value(b);
        };
        set<pair<int, int>, decltype(compare)> s(compare); 

        s.emplace(make_pair(0, 0));
        vector<pair<int, int>> v;
        for (size_t i = 0; i < k; i++) {
            pair<int, int> p = *s.begin();
            //cout << value(p) << "(" << expr(p) << ")" << ", ";
            v.push_back(p);

            s.erase(s.begin());
            s.emplace(make_pair(p.first + 1, p.second));
            s.emplace(make_pair(p.first, p.second + 1));
        }
        //cout << endl;
        return v;
    }

    vector<pair<int, int>> a_b_sqrt_o_n(size_t k) {
        int a = 0, b = 0;

        pair<int, int> next_inc_b = make_pair(a, b + 1);
        vector<pair<int, int>> v;

        for (size_t i = 0; i < k; i++) {
            v.push_back(make_pair(a, b));
            if (value(make_pair(a+1, b)) < value(next_inc_b)) {
                a++;
            } else {
                b++;
                next_inc_b = make_pair(a, b + 1);
            }
        }

        return v;
    }

    void test(size_t k) {
        auto r = a_b_sqrt_with_set(k);
        for(const auto & e: r) {
            cout << value(e) << "(" << expr(e) << ")" << ", ";
        }
        cout << endl;

        auto r_o_n = a_b_sqrt_o_n(k);
        for(const auto & e: r) {
            cout << value(e) << "(" << expr(e) << ")" << ", ";
        }
        cout << endl;
    }

}

void test_p14_07_a_b_sqrt() {
    PRINT_FUNC_NAME;
    p14_07::test(10);
}