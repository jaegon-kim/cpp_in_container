#include <iostream>
#include <vector>
#include <memory>

#include "utility/dump.hpp"
#include "linked_list.hpp"

using namespace std;
using namespace p7;

namespace p7_7 {

    void test(const vector<int> & v, int del_pos_from_last) {
        LinkedList<int> l = v2l(v);
        l.dump(false);
        l.delete_from_last(del_pos_from_last);
        cout << " -(delelete " << del_pos_from_last << "th from last )-> ";
        l.dump(true);
    }
}

void test_p7_7_remove_kth_from_last() {
    PRINT_FUNC_NAME;
    p7_7::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 5);
    p7_7::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10);
    p7_7::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0);
}
