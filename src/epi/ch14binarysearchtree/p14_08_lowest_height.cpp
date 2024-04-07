#include <iostream>
#include <vector>
#include <memory>
#include "utility/dump.hpp"

using namespace std;

namespace p14_08 {

    template <typename T>
    struct Node {
        Node(T v) : data{v} { }
        int height = 0;
        shared_ptr<Node> left = nullptr;
        shared_ptr<Node> right = nullptr;
        T data;
    };

    using node_ptr = shared_ptr<Node<int>>;

    pair<node_ptr, int> const_lowest_binarytree(const vector<int> & v, int s_idx, int e_idx) {
        int mid_idx = (e_idx - s_idx) / 2 + s_idx;
        node_ptr n = make_shared<Node<int>>(v[mid_idx]);
        int max_child_depth = 0;

        if (s_idx <= (mid_idx - 1)) {
            auto r = const_lowest_binarytree(v, s_idx, mid_idx - 1);
            n->left = r.first;
            if (r.second > max_child_depth) {
                max_child_depth = r.second;
            }
        }

        if ((mid_idx + 1) <= e_idx) {
            auto r = const_lowest_binarytree(v, mid_idx + 1, e_idx);
            n->right = r.first;
            if (r.second > max_child_depth) {
                max_child_depth = r.second;
            }
        }
        n->height = max_child_depth + 1;
        return make_pair(n, max_child_depth + 1);
    }

    void traverse(node_ptr node) {

        cout << node->data << "(" << node->height << ")" << ", ";

        if (node->left) {
            traverse(node->left);
        }
        if (node->right) {
            traverse(node->right);
        }
    }

    void test(const vector<int> & v) {
        auto r = const_lowest_binarytree(v, 0, v.size() - 1);
        node_ptr root = r.first;
        int height = r.second;

        cout << "height: " << height << endl;
        traverse(root);
        cout << endl;
    }
}

void test_p14_08_lowest_height() {
    PRINT_FUNC_NAME;
    p14_08::test(vector<int> {2, 3, 5, 7, 11, 13, 17, 19, 23});
}

