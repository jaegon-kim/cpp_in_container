#include <iostream>
#include <vector>
#include <memory>

#include "linked_list.hpp"
#include "utility/dump.hpp"

using namespace std;
using namespace p7;

namespace p7_8 {

    void test(const vector<int> & v) {
        LinkedList<int> l = v2l_sorted(v);
        l.dump(false);
        l.remove_duplicated();
        cout << " -> ";
        l.dump(true);
    }
}

void test_p7_8_remove_duplicated() {
    PRINT_FUNC_NAME;
    p7_8::test(vector<int> {0});
    p7_8::test(vector<int> {0, 0});
    p7_8::test(vector<int> {3, 4, 6, 1, 2, 9, 1, 3, 5, 6});
    p7_8::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    p7_8::test(vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    p7_8::test(vector<int> {9, 1, 3, 4, 5, 4, 3, 2, 1, 0});
    p7_8::test(vector<int> {9, 9, 3, 4, 5, 4, 3, 4, 1, 0});
    p7_8::test(vector<int> {9, 9, 3, 4, 5, 4, 0, 0, 1, 0});

}
