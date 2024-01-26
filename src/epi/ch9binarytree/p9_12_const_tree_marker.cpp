#include <iostream>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_12 {

    using node_ptr = shared_ptr<Node<char>>;

    node_ptr const_tree(char * pre, size_t & idx, size_t len) {

        if (idx == len) {
            cout << "error" << endl;
            return nullptr;
        }

        if (!pre[idx]) {
            cout << '-' << ", ";
            return nullptr;
        }

        node_ptr node = make_shared<Node<char>>(pre[idx]);
        cout << pre[idx] << ", ";

        node_ptr left = const_tree(pre, ++idx, len);
        node->left = left;

        node_ptr right = const_tree(pre, ++idx, len);
        node->right = right;

        return node;
    }

    void traverse(node_ptr node) {
        if (!node) {
            cout << '-' << ", ";
            return ;
        }
        cout << node->data << ", ";
        traverse(node->left);
        traverse(node->right);
    }

    void test() {
        char pre [] {'H', 'B', 'F', 0, 0, 'E', 'A', 0, 0, 0, 'C', 0, 'D', 0, 'G', 'I', 0, 0, 0};
        size_t idx = 0;
        node_ptr root = const_tree(pre, idx, sizeof(pre));
        cout << endl;
        traverse(root);
        cout << endl;
    }

}

void test_p9_12_const_tree_marker() {
    PRINT_FUNC_NAME;
    p9_12::test();
}