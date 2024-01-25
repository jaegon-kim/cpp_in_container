#include <iostream>
#include "utility/dump.hpp"
#include "binary_tree.hpp"

using namespace std;

namespace p9_9 {
    using node_ptr = shared_ptr<Node<int>>;
    //using node_ptr;
    node_ptr N(int v);
    node_ptr N(int v, node_ptr left, node_ptr right);
    void traverse(node_ptr node);
    node_ptr successor(node_ptr node);
}
using namespace p9_9;

namespace p9_10 {

    void traverse_s_1(node_ptr root) {
        node_ptr node = root;
        while(node->left) {
            node=node->left;
        }

        while(node) {
            cout << node->data << ", ";
            node = successor(node);
        }
        cout << endl;
    }

    void test() {
        node_ptr root = 
            N(314, N(6, N(271, N(28), N(0)), N(561, nullptr , N(3, nullptr, N(7)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(274, nullptr, N(28))));

            traverse(root);
            cout << endl;

            traverse_s_1(root);
    }

}

void test_p9_10_traverse_s_1() {
    PRINT_FUNC_NAME;
    p9_10::test();
}