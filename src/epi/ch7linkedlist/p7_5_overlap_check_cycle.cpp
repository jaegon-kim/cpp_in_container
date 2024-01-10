#include <iostream>
#include <vector>
#include <utility>

#include "linked_list.hpp"
#include "utility/dump.hpp"

using namespace std;
using namespace p7;

namespace p7_5 {

    void dump_rslt(std::pair<shared_ptr<Node<int>>, size_t> & p) {
        if (!p.first) {
            cout << " - no cycle" << endl;
        } else {
            cout << " - cycle start: " << p.first->data << ", cycle length: " << p.second << endl;
        }
    }

    void test(const vector<int> & v1, const vector<int> & v2, size_t v2_link_pos, size_t target, size_t source) {

        cout << "v1: ";
        dump_vec<int>(v1, true);
        cout << "v2: ";
        dump_vec<int>(v2, true);
        cout << "v2_link_pos: " << v2_link_pos << endl;

        LinkedList<int> l1 = v2l(v1);
        LinkedList<int> l2 = v2l(v2);
        l2.link(l1, v2_link_pos);
        l2.set_cycle(target, source);

        cout << "cycled v1: ";
        l1.dump(true);
        cout << "cycled v2: ";
        l2.dump(true);

        auto rslt_1 = l1.find_cycle();
        //dump_rslt(rslt_1);
        auto rslt_2 = l2.find_cycle();
        //dump_rslt(rslt_2);

        if (rslt_1.first != rslt_2.first) {
            cout << "linked position: " << rslt_1.first->data << " and " << rslt_2.first->data << endl;
            return;
        } else if (rslt_1.first) {
            shared_ptr<Node<int>> linked_node = l2.get_linked_node(l1, rslt_1.first);
            cout << "linked position: " << linked_node->data << endl;
        }
    }
}

void test_p7_5_test_overlap_check_cycle() {
    PRINT_FUNC_NAME;
    p7_5::test(vector<int>{10, 11, 12, 13, 14}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 3, 2, 6);

    p7_5::test(vector<int>{10, 11, 12, 13, 14}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 3, 4, 6);

}
