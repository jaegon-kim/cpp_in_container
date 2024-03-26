#include <iostream>
#include <optional>

#include "epi/ch9binarytree/binary_tree.hpp"
#include "utility/dump.hpp"

using namespace std;

namespace p14_01 {

    using node_ptr = shared_ptr<Node<int>>;

    node_ptr N(int v) {
        node_ptr new_node = make_shared<Node<int>>(v);
        return new_node;
    }

    node_ptr N(int v, node_ptr left, node_ptr right) {
        node_ptr new_node = make_shared<Node<int>>(v);
        new_node->left = left;
        new_node->right = right;
        return new_node;
    }

    optional<pair<int, int>> traverse(node_ptr n) {

        pair<int, int> range;

        if (n->left) {
            optional<pair<int, int>> r = traverse(n->left);
            if (!r) {
                return nullopt;
            } 
            if (r.value().first > n->data || r.value().second > n->data) {
                return nullopt;
            }
            range.first = r.value().first;
        } else {
            range.first = n->data;
        }

        if (n->right) {
            optional<pair<int, int>> r = traverse(n->right);
            if (!r) {
                return nullopt;
            }
            if (r.value().first < n->data || r.value().second < n->data) {
                return nullopt;
            }
            range.second = r.value().second;
        } else {
            range.second = n->data;
        }

        cout << n->data << ", ";
        return range;
    }

    void check(const optional<pair<int, int>> & r) {
        if (!r) {
            cout << "invalid binary search tree" << endl;
        } else {
            cout << "(" << r.value().first << ", " << r.value().second << ")" << endl;
        }
    }

    void test() {

        check(traverse(
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            )
        ));


        check(traverse(
            N(19, N(7, N(3, N(4), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            )
        ));

        check(traverse(
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(2))
                  )
            )
        ));

    }

}


void test_p14_01_check_bst() {
    PRINT_FUNC_NAME;
    p14_01::test();
}
