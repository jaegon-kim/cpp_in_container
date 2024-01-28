#include <iostream>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_14 {
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

    void left_exterior(node_ptr node) {
        if (!node->left) {
            return;
        }
        cout << node->data << ", ";
        left_exterior(node->left);
    }

    void right_exterior(node_ptr node) {
        if (!node->right) {
            return;
        }
        right_exterior(node->right);
        cout << node->data << ", ";
    }

    void traverse_leaf(node_ptr node) {
        if (!node) {
            return;
        }
        if (!node->left && !node->right) {
            cout << node->data << ", ";
        }
        traverse_leaf(node->left);
        traverse_leaf(node->right);
    }

    void test() {
        node_ptr root = 
            N(314, N(6, N(271, N(28), N(0)), N(561, nullptr , N(3, nullptr, N(17)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(271, nullptr, N(28))));

        left_exterior(root);
        traverse_leaf(root);
        right_exterior(root->right);

    }
}

void test_p9_14_exterior_node() {
    PRINT_FUNC_NAME;
    p9_14::test();
}