#include <iostream>
#include <vector>
#include <memory>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

namespace p9_13 {

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

    void traverse(node_ptr node, vector<node_ptr> & list) {
        if (!node) {
            return;
        }
        if (!node->left && !node->right) {
            //cout << node->data << ", ";
            list.emplace_back(node);
        }
        traverse(node->left, list);
        traverse(node->right, list);
    }

    void test() {
        node_ptr root = 
            N(314, N(6, N(271, N(28), N(0)), N(561, nullptr , N(3, nullptr, N(17)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(274, nullptr, N(28))));

        vector<node_ptr> v;
        traverse(root, v);
        
        for (node_ptr node: v) {
            cout << node->data << ", ";
        }
        cout << endl;
    }

}

void test_p9_13_leaf_list() {
    PRINT_FUNC_NAME;
    p9_13::test();

}