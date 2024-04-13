#include <iostream>
#include "utility/dump.hpp"
#include "memory"

using namespace std;

namespace p14_09 {

    
    template <typename T>
    struct Node {
        
        Node(T t) : data{t} {}
        shared_ptr<Node<T>> parent = nullptr;
        shared_ptr<Node<T>> left = nullptr;
        shared_ptr<Node<T>> right = nullptr;
        T data;
    };

    using node_ptr = shared_ptr<Node<int>>;

    node_ptr N(int v) {
        node_ptr new_node = make_shared<Node<int>>(v);
        return new_node;
    }

    node_ptr N(int v, node_ptr left, node_ptr right) {
        node_ptr new_node = make_shared<Node<int>>(v);
        new_node->left = left;
        if (left) {
            left->parent = new_node;
        }
        new_node->right = right;
        if (right) {
            right->parent = new_node;
        }
        return new_node;
    }

    node_ptr get_node(node_ptr n, int v) {
        if (n->data == v) {
            return n;
        }
        if (n->left) {
            auto r = get_node(n->left, v);
            if (r) {
                return r;
            }
        }
        if (n->right) {
            auto r = get_node(n->right, v);
            if (r) {
                return r;
            }
        }
        return nullptr;
    }

    bool check_ancester(node_ptr m, node_ptr a) {
        while(m) {
            if (m == a) {
                return true;
            }
            if (m) {
                m = m->parent;
            }
        }
        return false;
    }

    bool check_complete_sort(node_ptr m, node_ptr n1, node_ptr n2) {

        node_ptr s1 = n1, s2 = n2;
        while(s1 || s2) {
            if (s1 == m) {
                return check_ancester(m, n2);
            }

            if (s2 == m) {
                return check_ancester(m, n1);
            }

            if (s1) {
                s1 = s1->parent;
            }

            if (s2) {
                s2 = s2->parent;
            }
        }
        cout << "failed to fnd " << endl;
        return false;
    }


    void test() {
        node_ptr root = 
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            );

        node_ptr j = get_node(root, 23);
        node_ptr a = get_node(root, 19);
        node_ptr k = get_node(root, 37);
        node_ptr i = get_node(root, 43);
        node_ptr m = get_node(root, 31);
        node_ptr p = get_node(root, 53);

        cout << "j: " << (j ? j->data:0) << endl;
        cout << "a: " << (a ? a->data:0) << endl;
        cout << "k: " << (k ? k->data:0) << endl;
        cout << "i: " << (i ? i->data:0) << endl;
        cout << "m: " << (m ? m->data:0) << endl;
        cout << "p: " << (p ? p->data:0) << endl;
        
        cout << check_complete_sort(j, a, k) << endl;
        cout << check_complete_sort(j, i, m) << endl;
        cout << check_complete_sort(j, i, p) << endl;
        cout << check_complete_sort(j, j, k) << endl;

    }
}

void test_p14_09_check_complete_sort() {
    PRINT_FUNC_NAME;
    p14_09::test();
}