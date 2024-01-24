#include <iostream>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_8 {

    using node_ptr = shared_ptr<Node<int>>;

    node_ptr N(int v) {
        node_ptr new_node = make_shared<Node<int>>(v);
        new_node->num_child = 0;
        return new_node;
    }

    node_ptr N(int v, node_ptr left, node_ptr right) {
        node_ptr new_node = make_shared<Node<int>>(v);
        new_node->left = left;
        new_node->right = right;
        if (left) {
            new_node->num_child += (left->num_child + 1);
        }
        if (right) {
            new_node->num_child += (right->num_child + 1);
        }
        return new_node;
    }

    // 재귀를 이용한 중위순회 (inorder traverse)
    void traverse(node_ptr node) {
        if (!node) {
            return;
        }
        traverse(node->left);
        cout << node->data << "(" << node->num_child << "), ";
        traverse(node->right);
    }


    node_ptr find_kth(node_ptr node, size_t k) {
        if (!node) {
            //cout << "!" << endl;
            return nullptr;
        }

        size_t num_l_child = 0;
        if (node->left) {
            num_l_child = 1 + node->left->num_child;
        }

        if (k <= num_l_child) {
            return find_kth(node->left, k);
        }

        if (k == (num_l_child + 1)) {
            return node;
        }

        return find_kth(node->right, k - (num_l_child + 1));
    }

    void test() {
        node_ptr root = 
            N(314, N(6, N(271, N(28), N(0)), N(561, nullptr , N(3, nullptr, N(7)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(274, nullptr, N(28))));
        traverse(root);
        cout << endl;

        for (size_t i = 1; i <= 16; i++) {
            node_ptr found = find_kth(root, i);
            if (found) {
                cout << found->data << "(" << found->num_child << "), ";
            } else {
                cout << "failed to find " << i << "th element" << endl;
            }
        }
        cout << endl;

        for (size_t i: {0, 17}) {
            node_ptr found = find_kth(root, i);
            if (found) {
                cout << found->data << "(" << found->num_child << "), ";
            } else {
                cout << "failed to find " << i << "th element" << endl;
            }
        }
    }
}

void test_p9_8_k_th_ele_in_inorder_traverse() {
    PRINT_FUNC_NAME;
    p9_8::test();
}