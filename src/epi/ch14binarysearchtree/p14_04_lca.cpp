#include <iostream>
#include <optional>

#include "utility/dump.hpp"
#include "epi/ch9binarytree/binary_tree.hpp"

using namespace std;

namespace p14_04 {
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

    // a < b (a is smaller than b)
    // LCA(Least Common Ancestor)는 후위순회를 활용한다.
    node_ptr traverse(node_ptr ptr, int a, int b, node_ptr & tgt) {

        node_ptr rl = nullptr, rr = nullptr;

        if (ptr->data == a) {
            rl = ptr;
            if (ptr->right) {
                rr = traverse(ptr->right, a, b, tgt);
            }           
        } else if (ptr->data == b) {
            rr = ptr;
            if (ptr->left) {
                rl = traverse(ptr->left, a, b, tgt);
            }           
        } else {
            if (ptr->left) {
                rl = traverse(ptr->left, a, b, tgt); 
                if (tgt) {
                    return nullptr;
                }         
            }

            if (ptr->right) {
                rr = traverse(ptr->right, a, b, tgt);
                if (tgt) {
                    return nullptr;
                }
            }
        } 

        if (rl && rr) {
            tgt = ptr;
            return nullptr;
        }

        if (rl) {
            return rl;
        }

        if (rr) {
            return rr;
        }

        return nullptr;
    }

    pair<int, int> min_max(int a, int b) {
        if (a > b) {
            return make_pair(b, a);
        } else {
            return make_pair(a, b);
        }
    }

    void test(node_ptr root, int a, int b) {
        node_ptr tgt = nullptr;
        auto p = min_max(a, b);
        traverse(root, p.first, p.second, tgt = nullptr);

        cout << "{" << p.first << ", " << p.second << "} "; 
        if (tgt) {
            cout << tgt->data << endl;
        } else {
            cout << "failed to find" << endl;
        }
    }

    void test() {
        node_ptr tgt = nullptr;
        node_ptr root = 
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            );

        test(root, 3, 17);
        test(root, 3, 53);
        test(root, 1, 53);
        test(root, 23, 37);
        test(root, 2, 3);
    }
}

void test_p14_04_lca() {
    PRINT_FUNC_NAME;
    p14_04::test();    
}