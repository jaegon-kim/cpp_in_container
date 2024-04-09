#include <iostream>
#include <vector>
#include <memory>
#include <set>

#include "utility/dump.hpp"

using namespace std;

namespace p14_10 {

    template <typename T>
    struct Node {
        Node(T v) : data{v} {}
        shared_ptr<Node> left = nullptr;
        shared_ptr<Node> right = nullptr;
        T data;
    };

    using node_ptr = shared_ptr<Node<int>>;

    node_ptr N(int v, node_ptr left, node_ptr right) {
        node_ptr n = make_shared<Node<int>>(v);
        n->left = left;
        n->right = right;
        return n;
    }

    node_ptr N(int v) {
        return make_shared<Node<int>>(v);
    }

    bool traverse(node_ptr n, int s, int e, vector<int> & v) {

        if (n->left) {
            if(!traverse(n->left, s, e, v)) {
                return false;
            }
        }
        if (n->data >= s && n->data <= e) {
            v.push_back(n->data);
        }
        //cout << n->data << ", ";
        if (n->data > e) {
            return false;
        }

        if (n->right) {
            if (!traverse(n->right, s, e, v)) {
                return false;
            }
        }

        return true;
    }

    vector<int> get_range_with_bt(node_ptr root, int s_v, int e_v) {
        vector<int> v;
        traverse(root, s_v, e_v, v);
        return v;
    }

    vector<int> get_range_with_set(set<int> & s, int s_v, int e_v) {
        vector<int> v;
        for(auto iter = s.begin(); iter != s.end(); iter++) {
            if ((*iter) >= s_v && (*iter) <= e_v) {
                v.push_back(*iter);
            }
            if ((*iter) > e_v) {
                break;
            }
        }
        return v;
    }

    void test() {
        node_ptr n = 
            N(19, N(7, N(3, N(2), N(5)),
                       N(11, nullptr, N(17, N(13), nullptr)) 
                  ),
                  N(43, N(23, nullptr, N(37, N(29, nullptr, N(31)), N(41))),
                        N(47, nullptr, N(53))
                  )
            );
        dump_vec(get_range_with_bt(n, 16, 31), true);

        set<int> s {19, 7, 3, 2, 5, 11, 17, 13, 43, 23, 37, 29, 31, 41, 47, 53};
        dump_vec(get_range_with_set(s, 16, 31), true);

    } 
}

void test_p14_10_get_range() {
    PRINT_FUNC_NAME;
    p14_10::test();
}