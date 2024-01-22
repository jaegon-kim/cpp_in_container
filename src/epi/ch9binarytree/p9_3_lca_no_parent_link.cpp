#include <iostream>
#include <memory>

#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_3 {

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

    node_ptr find_lca(node_ptr node, node_ptr n0, node_ptr n1, node_ptr & lca) {
        if (!node) {
            return nullptr;
        }

        if (node == n0 || node == n1) {
            return node;
        }

        node_ptr l = find_lca(node->left, n0, n1, lca);
        if (lca) {
            return nullptr;
        }

        node_ptr r = find_lca(node->right, n0, n1, lca);
        if (lca) {
            return nullptr;
        }

        if (l && r) {
            lca = node;
            return nullptr;
        }

        if (l) {
            return l;
        }

        if (r) {
            return r;
        }
        return nullptr;
    }

    void test() {
        node_ptr node_0 = N(641);
        node_ptr node_1 = N(28);
        node_ptr node_2 = N(0);
        node_ptr node_3 = N(0);
        node_ptr node_4 = N(257);
        node_ptr lca = nullptr;
        node_ptr root = 
            N(314, N(6, N(271, N(28), node_2), N(561, nullptr , N(3, nullptr, N(7)))), 
                N(6, N(2, N(1, N(401, nullptr, node_0), node_4), nullptr), N(274, nullptr, node_1)));

        find_lca(root, node_0, node_1, lca);
        cout << (lca? lca->data: -1) << endl;

        lca = nullptr;
        find_lca(root, node_1, node_2, lca);
        cout << (lca? lca->data: -1) << endl;

        lca = nullptr;
        find_lca(root, node_4, node_0, lca);
        cout << (lca? lca->data: -1) << endl;
    }

}

void test_p9_3_lca_no_parent_link() {
    PRINT_FUNC_NAME;
    p9_3::test();
}