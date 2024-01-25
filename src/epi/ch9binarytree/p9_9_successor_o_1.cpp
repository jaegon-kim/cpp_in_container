#include <iostream>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_9 {

    using node_ptr = shared_ptr<Node<int>>; 

    node_ptr N(int v) {
        node_ptr new_node = make_shared<Node<int>>(v);
        return new_node;
    }

    node_ptr N(int v, node_ptr left, node_ptr right) {
        node_ptr new_node = make_shared<Node<int>>(v);
        new_node->left = left;
        new_node->right = right;
        if (left) {
            left->parent = new_node;
        }
        if (right) {
            right->parent = new_node;
        }
        return new_node;
    }

    void dump(__attribute__((unused)) int line, __attribute__((unused)) node_ptr node) {
        //cout << (node?node->data:0) << "(line: " << line << ")->" << endl;
    }

    node_ptr successor(node_ptr node) {
        node_ptr s;
        if (node->right) {
            s = node->right;
            dump(__LINE__, s);
            while(s->left) {
                s = s->left;
                dump(__LINE__, s);
            }
            return s;
        }

        s = node->parent;
        dump(__LINE__, s);
        if (!s) {
            return nullptr;
        }

        if (node == s->left) {
            return s;
        }

        node_ptr p = s->parent;
        dump(__LINE__, p);
        while(p && s != p->left) {
            s = p;
            p = p->parent;
            dump(__LINE__, p);
            dump(__LINE__, s);
        }
        dump(__LINE__, p);

        if (!p) {
            return nullptr;
        }
        return p;
    }

    void traverse(node_ptr node) {
        if (!node) {
            return;
        }
        traverse(node->left);
        cout << node->data << ", ";
        traverse(node->right);
    }

    void test() {
        node_ptr node_0 = N(641);
        node_ptr node_1 = N(28);
        node_ptr node_2 = N(0);
        node_ptr node_3 = N(0);
        node_ptr node_4 = N(257);
        node_ptr root = 
            N(314, N(6, N(271, N(28), node_2), N(561, nullptr , N(3, nullptr, N(7)))), 
                N(6, N(2, N(1, N(401, nullptr, node_0), node_4), nullptr), N(274, nullptr, node_1)));

        traverse(root);
        cout << endl;

        for (node_ptr n: {node_0, node_1, node_2, node_3, node_4}) {
            cout << n->data << "=>";
            node_ptr s = successor(n);
            cout << (s? s->data : -1) << endl;
        }

    }
}

void test_p9_9_successor_o_1() {
    PRINT_FUNC_NAME;
    p9_9::test();
}