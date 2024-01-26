#include <iostream>
#include <string>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_11 {

    using node_ptr = shared_ptr<Node<char>>;

    int find(string & str, char c) {
        size_t len = str.length();
        for (size_t i = 0; i < len; i++) {
            if (str[i] == c) {
                return i;
            }
        }
        return -1;
    } 

    void traverse_inorder(node_ptr node) {
        if (!node) {
            return;
        }
        traverse_inorder(node->left);
        cout << node->data << ", ";
        traverse_inorder(node->right);
    }

    void traverse_preorder(node_ptr node) {
        if (!node) {
            return;
        }
        cout << node->data << ", ";
        traverse_preorder(node->left);
        traverse_preorder(node->right);
    }

    node_ptr partion(string in, string & pre, size_t & idx) {
        int in_len = (int) in.length();
        if (in_len == 1) {
            return make_shared<Node<char>>(in[0]);
        }

        int root_idx = find(in, pre[idx]);
        if (root_idx == -1) {
            cout << "error" << endl;
            return nullptr;
        }
        node_ptr node = make_shared<Node<char>>(in[root_idx]);
        cout << "finding " << pre[idx] << " at " << root_idx << " in " << in << endl;

        string left, right;

        if (!root_idx) {
            left = "";
        } else {
            left = in.substr(0, root_idx);
        }

        if (root_idx == (in_len - 1)) {
            right = "";
        } else {
            right = in.substr(root_idx + 1, (in_len - 1));
        }

        cout << "L:" << left << ", R:" << right << endl;
         
        if (left.length()) {
            node_ptr l_child = partion(left, pre, ++idx);
            node->left = l_child;
        }
        if (right.length()) {
            node_ptr r_child = partion(right, pre, ++idx);
            node->right = r_child;
        }

        return node;
    }

    void test() {
        string preorder = "HBFEACDGI";
        string inorder  = "FBAEHCDIG";
        size_t preorder_idx = 0;
        cout << inorder << endl;
        node_ptr root = partion(inorder, preorder, preorder_idx);
        traverse_inorder(root);
        cout << endl;
        traverse_preorder(root);
        cout << endl;
    }
}

void test_p9_11_const_tree() {
    PRINT_FUNC_NAME;

    p9_11::test();

}
