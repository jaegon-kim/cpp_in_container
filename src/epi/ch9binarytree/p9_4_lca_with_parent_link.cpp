#include <iostream>
#include <memory>

#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_4 {
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

    int height(node_ptr root, node_ptr n) {
        int c = 0;
        while(root != n) {
            n = n->parent;
            c++;
        }
        return c;
    }

    node_ptr ancestor(node_ptr n, int h) {
        int cnt = 0;
        while(cnt != h) {
            n = n->parent;
            cnt++;
        }
        return n;
    }

    node_ptr find_lca(node_ptr root, node_ptr n0, node_ptr n1) {

       node_ptr s0 = n0, s1 = n1;
        int h0 = height(root, s0);
        int h1 = height(root, s1);

        if (h0 > h1) {
            s0 = ancestor(s0, h0 - h1);
        } else {
            s1 = ancestor(s1, h1 - h0);
        }
 
        //cout <<"h0: " << h0 << ", s0: " << s0->data << ", ";
        //cout <<"h1: " << h1 << ", s1 "  << s1->data << endl;

        while(s0 != s1) {
            s0 = s0->parent;
            s1 = s1->parent;
        }
        return s0;
        return nullptr;
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

        node_ptr lca;
        lca = find_lca(root, node_0, node_1);
        cout << (lca? lca->data: -1) << endl;

        lca = find_lca(root, node_1, node_2);
        cout << (lca? lca->data: -1) << endl;

        lca = find_lca(root, node_4, node_0);
        cout << (lca? lca->data: -1) << endl;

    }

}

void test_p9_4_lca_with_parent_link() {
    PRINT_FUNC_NAME;
    p9_4::test();
}
