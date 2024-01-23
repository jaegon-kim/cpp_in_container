#include <iostream>
#include <list>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_7 {

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

    // 재귀를 이용한 중위순회 (inorder traverse)
    void traverse(node_ptr node) {
        if (!node) {
            return;
        }
        traverse(node->left);
        cout << node->data << ", ";
        traverse(node->right);
    }

    // loop를 이용한 중위순회 
    void traverse_loop(node_ptr root) {
        node_ptr node = root;
        list<node_ptr> stack;

        while(node) {
            stack.push_front(node);
            node = node->left;
        };

        while(!stack.empty()) {
            node = stack.front();
            stack.pop_front();
            cout << node->data << ", ";

            if (node->right) {
                node = node->right;

                while(node) {
                    stack.push_front(node);
                    node = node->left;
                };
            }
        }
        cout << endl;
    }

    void test() {
        node_ptr root = 
            N(314, N(6, N(271, N(28), N(0)), N(561, nullptr , N(3, nullptr, N(7)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(274, nullptr, N(28))));
        traverse(root);
        cout << endl;

        traverse_loop(root);
    }
}

void test_p9_7_inorder_traverse_loop() {
    PRINT_FUNC_NAME;
    p9_7::test();
}