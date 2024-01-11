#include <iostream>
#include <vector>
#include <memory>
#include "linked_list.hpp"
#include "utility/dump.hpp"

using namespace std;
using namespace p7;

namespace p7_6 {
    void test(const vector<int> & v, int delete_pos) {
        
        LinkedList<int> l = p7::v2l(v);
        l.dump(false); cout << " delete: " << delete_pos << endl;
        shared_ptr<Node<int>> delete_node = l.get_node(delete_pos);
        l.delete_non_last_node(delete_node);
        cout << " -> ";
        l.dump(true);
    }
}

void test_p7_6_delete_o_1() {
    PRINT_FUNC_NAME;
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
    p7_6::test(v, 5);
}