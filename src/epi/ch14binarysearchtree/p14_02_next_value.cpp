#include <iostream>


#include "epi/ch9binarytree/binary_tree.hpp"
#include "utility/dump.hpp"

using namespace std;

namespace p14_02 {

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

    enum OP {GO, FOUND, STOP};
    void traverse(node_ptr n, int s, pair<OP, int> & status) {

        switch(status.first) {
            case FOUND:
                status.first = STOP;
                status.second = n->data;
                return;
            case STOP:
                return;
            case GO:
                break;
        }

        if (n->left) {
            traverse(n->left, s, status);
        }

        switch(status.first) {
            case FOUND:
                status.first = STOP;
                status.second = n->data;
                return;
            case STOP:
                return;
            case GO:
                break;
        }
        cout << n->data << ", ";
        if (n->data == s) {
            status.first = FOUND;            
        }

        if (n->right) {
            traverse(n->right, s, status);
        }
    }

    void test() {

        pair<OP, int> status = make_pair(GO, -1);
        traverse(
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            ),
            37,
            status
        );
        cout << endl;
        cout << status.second << " " << endl;
    }
}

void test_p14_02_next_value() {
    PRINT_FUNC_NAME;
    p14_02::test();
}