#include <iostream>
#include <vector>
#include "utility/dump.hpp"
using namespace std;
namespace p17_05 {

    pair<char, int> major_ele(const vector<char> & v) {

        pair<char, int> p = make_pair(v[0], 1);

        for (size_t i = 1; i < v.size(); i++) {
            if (!p.second) {
                p.first = v[i];
                p.second = 1;
                continue;
            }

            if (p.first == v[i]) {
                p.second++;
            } else {
                p.second--;
            }
        }
        return p;
    }

    void test(const vector<char> & v) {

        auto p = major_ele(v);
        cout << p.first << ", " << p.second << endl;
    }
}

void test_p17_05_finding_major_ele() {
    PRINT_FUNC_NAME;
    p17_05::test(vector<char> {'b', 'a', 'c', 'a', 'a', 'b', 'a', 'a', 'c', 'a'});
    p17_05::test(vector<char> {'a'});
    p17_05::test(vector<char> {'a', 'a'});
    p17_05::test(vector<char> {'a', 'b', 'a'});
    p17_05::test(vector<char> {'a', 'b', 'a', 'c', 'a'});
    p17_05::test(vector<char> {'a', 'b', 'a', 'a', 'c', 'a'});


}