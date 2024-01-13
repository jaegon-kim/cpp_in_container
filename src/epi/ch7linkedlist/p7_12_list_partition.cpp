#include <iostream>
#include <vector>
#include <memory>

#include "utility/dump.hpp"
#include "linked_list.hpp"

using namespace std;
using namespace p7;

namespace p7_12 {


    void test(const vector<int> & v) {
        LinkedList<int> l = v2l(v);
        l.dump(false);
        int pivot_idx = v.size() / 2;
        int pivot = l.get_node(pivot_idx)->data;
        cout << "-(partition with " << pivot << ")->";
        l.partition(pivot);
        l.dump(true);
    }
}


void test_p7_12_list_partition() {
    PRINT_FUNC_NAME;
    p7_12::test(vector<int> {3, 4, 6, 1, 2, 3, 1, 9, 3, 5, 6});
    p7_12::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    p7_12::test(vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1, 0});
    p7_12::test(vector<int> {9, 1, 3, 4, 5, 4, 3, 2, 1, 0});
    p7_12::test(vector<int> {9, 9, 3, 4, 5, 4, 3, 4, 1, 0});
    p7_12::test(vector<int> {9, 9, 3, 4, 5, 4, 0, 0, 1, 0});
}