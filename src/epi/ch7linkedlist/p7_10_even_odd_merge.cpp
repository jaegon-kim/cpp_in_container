#include <iostream>
#include <vector>
#include <memory>

#include "utility/dump.hpp"
#include "linked_list.hpp"

using namespace std;
//using namespace p7;

namespace p7_10 {

    void test(const vector<int> & v) {
        p7::LinkedList<int> l = p7::v2l<int>(v);
        l.dump(false);
        l.even_odd_merge();
        cout << " -> ";
        l.dump(true);
    }
}

void test_p7_10_even_odd_merge() {
    PRINT_FUNC_NAME;
    p7_10::test(vector<int> {0});
    p7_10::test(vector<int> {0, 1});
    p7_10::test(vector<int> {0, 1, 2});
    p7_10::test(vector<int> {0, 1, 2, 3});
    p7_10::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
}