#include <iostream>
#include <vector>
#include <optional>
#include <memory>

#include "utility/dump.hpp"
#include "epi/ch9binarytree/binary_tree.hpp"

using namespace std;

namespace p14_05 {

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

    void preorder_traverse_log(node_ptr ptr, vector<optional<int>> & log_v) {

        log_v.push_back(make_optional(ptr->data));

        if (ptr->left) {
            preorder_traverse_log(ptr->left, log_v);
        } else {
            log_v.push_back(nullopt);
        }

        if (ptr->right) {
            preorder_traverse_log(ptr->right, log_v);
        } else {
            log_v.push_back(nullopt);
        }
    }

    enum traverse_type {PRE, IN, POST};
    void traverse(node_ptr ptr, traverse_type t) {
        if (t == PRE) {
            cout << ptr->data << ", ";
        }
        if (ptr->left) {
            traverse(ptr->left, t);
        }
        if (t == IN) {
            cout << ptr->data << ", ";
        }
        if (ptr->right) {
            traverse(ptr->right, t);
        }
        if (t == POST) {
            cout << ptr->data << ", ";
        }
    }

    void dump(vector<optional<int>> & v) {
        cout << "{";
        for(const auto & opt: v) {
            if (!opt) {
                cout << "E, "; 
            } else {
                cout << opt.value() << ", ";
            }
        }
        cout << "}" << endl;
    }

    node_ptr build(vector<optional<int>> & v, int & idx) {
        node_ptr node = make_shared<Node<int>>(v[idx].value());

        if (v[++idx]) {
            node_ptr left = build(v, idx);
            node->left = left;   
        }

        if (v[++idx]) {
            node_ptr right = build(v, idx);
            node->right = right;
        }

        return node;
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


        vector<optional<int>> log_v;
        preorder_traverse_log(root, log_v);
        //cout << endl; 
        dump(log_v);
        int idx = 0;
        node_ptr root2 = build(log_v, idx);
        traverse(root2, PRE);
        cout << endl;
        traverse(root2, IN);
        cout << endl;
    }
}

void test_p14_05_const_tree_inorder_log() {
    PRINT_FUNC_NAME;
    p14_05::test();
}