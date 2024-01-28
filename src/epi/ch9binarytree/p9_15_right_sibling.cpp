#include <iostream>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_15 {

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

    void const_right_sibling(node_ptr node) {
        if (!node) {
            return;
        }
        if (node->left) {
            node->left->next = node->right;
        }
        const_right_sibling(node->left);
        const_right_sibling(node->right);        
    }

    void traverse(node_ptr node) {
        if (!node) {
            return;
        }

        cout << node->data << "( next: " << (node->next? node->next->data: 0) << "), ";

        traverse(node->left);
        traverse(node->right);
    }


    void test() {
        node_ptr root = 
            N(314, N(6, N(271, N(28), N(0)), N(561, nullptr , N(3, nullptr, N(17)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(274, nullptr, N(28))));

        const_right_sibling(root);
        traverse(root);
        cout << endl;
    }
}

void test_p9_15_right_sibling() {
    PRINT_FUNC_NAME;
    p9_15::test();
}