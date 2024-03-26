#include <iostream>

#include "epi/ch9binarytree/binary_tree.hpp"
#include "utility/dump.hpp"

using namespace std;

namespace p14_03 {

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

    void traverse(node_ptr node, size_t n, vector<int> & v) {
        if (node->right) {
            traverse(node->right, n, v);
        }
        cout << node->data << ", ";
        if (v.size() < n) {
            v.push_back(node->data);
        }
        if (node->left) {
            traverse(node->left, n, v);
        }
    }

    void test() {

        vector<int> v;
        traverse(
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            ),
            3,
            v
        );
        dump_vec(v, true);
    }
}

void test_p14_03_k_max_values() {
    PRINT_FUNC_NAME;
    p14_03::test();
}