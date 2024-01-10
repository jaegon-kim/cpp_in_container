#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include "utility/dump.hpp"

#include "linked_list.hpp"

using namespace std;
using namespace p7;


namespace p7_4 {

    void test(const vector<int> & v1, const vector<int> & v2, size_t v2_link_pos) {
        LinkedList<int> l1 = v2l(v1);
        LinkedList<int> l2 = v2l(v2);
        l2.link(l1, v2_link_pos);
        l1.dump(true);
        l2.dump(true);

        if (l2.is_overlap(l1)) {
            cout << "overlapped lists ";
            shared_ptr<Node<int>> linked_node = l2.get_linked_node(l1);
            cout << "(overlapping start: " << linked_node->data << ")" << endl;
        }
    }
}

void test_p7_4_overlap_check() {
    PRINT_FUNC_NAME;
    p7_4::test(vector<int>{10, 11, 12, 13, 14}, vector<int>{0, 1, 2, 3, 4, 5}, 3);
    p7_4::test(vector<int>{10, 11, 12, 13, 14}, vector<int>{0, 1, 2, 3, 4, 5}, 0);
    p7_4::test(vector<int>{10, 11, 12, 13, 14}, vector<int>{0, 1, 2, 3, 4, 5}, 5);
}