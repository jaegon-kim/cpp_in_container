#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p17_06 {

    int rich_city(const vector<tuple<char, int, int>> & cities) {

        vector<int> a(cities.size());
        for (size_t i = 0; i < cities.size(); i++) {
            a[i] = get<1>(cities[i]) - (get<2>(cities[i])/20);
        }
        dump_vec(a, true);

        int sum = 0, max = 0, max_idx = -1;
        for (size_t i = 0; i < a.size(); i++) {
            sum += a[i];
            if (a[i] > max) {
                max = a[i];
                max_idx = i;
            }
        }

        cout << "sum: " << sum << endl;

        if (sum >= 0) {
            return max_idx;
        } else {
            return -1;
        }
    }
    
    void test(const vector<tuple<char, int, int>> & cities) {

        auto r = rich_city(cities);
        if (r == -1) {
            cout << "rich city: not exist" << endl;
        } else {
            cout << "rich city: " << get<0>(cities[r]) << endl;
        }

        

    }
}

void test_p17_06_reach_city() {
    PRINT_FUNC_NAME;
    vector<tuple<char, int, int>> cities = {
        {'a', 50, 900},
        {'b', 20, 600},
        {'c',  5, 200},
        {'d', 30, 400},
        {'e', 25, 600},
        {'f', 10, 200},
        {'g', 10, 100},
    };

    p17_06::test(cities);
}