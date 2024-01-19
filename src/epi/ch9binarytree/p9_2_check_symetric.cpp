#include <iostream>
#include <memory>
#include <list>

#include "utility/dump.hpp"

using namespace std;

namespace p9_2 {

    template <typename T>
    struct Node {
        Node(T v) : data(v) {}
        T data;
        shared_ptr<Node<T>> left = nullptr;
        shared_ptr<Node<T>> right = nullptr;
    };

    template <typename T>
    shared_ptr<Node<int>> N(T v) {
        shared_ptr<Node<int>> new_node = make_shared<Node<int>>(v);
        return new_node;
    }

    template <typename T>
    shared_ptr<Node<int>> N(T v, shared_ptr<Node<int>> left, shared_ptr<Node<int>> right) {
        shared_ptr<Node<int>> new_node = make_shared<Node<int>>(v);
        new_node->left = left;
        new_node->right = right;
        return new_node;
    }


    template <typename T>
    bool is_symetric(shared_ptr<Node<T>> root) {

        list<shared_ptr<Node<T>>> left_stack;
        list<shared_ptr<Node<T>>> right_stack;

        shared_ptr<Node<T>> left = root->left;
        shared_ptr<Node<T>> right = root->right;

        while(true) {
            cout << "left: " << left->data << ", right: " << right->data << endl;

            if (left->left) {
                if (!right->right) {
                    cout << left->data << " and " << right->data << " are not symetric" << endl;
                    return false;
                }
                left_stack.push_front(left->left);
                right_stack.push_front(right->right);
            } else {
                if (right->right) {
                    cout << left->data << " and " << right->data << " are not symetric" << endl;
                    return false;
                }
            }

            if (left->right) {
                if (!right->left) {
                    cout << left->data << " and " << right->data << " are not symetric" << endl;
                    return false;
                }
                left_stack.push_front(left->right);
                right_stack.push_front(right->left);
            } else {
                if (right->left) {
                    cout << left->data << " and " << right->data << " are not symetric" << endl;
                    return false;
                }
            }

            if (left_stack.empty() || right_stack.empty()) {
                break;
            } 

            left = left_stack.front();
            left_stack.pop_front();

            right = right_stack.front();
            right_stack.pop_front();            
        }

        if (!left_stack.empty()) {
            cout << left_stack.front()->data << " is not symetric" << endl;
            return false;
        }

        if (!right_stack.empty()) {
            cout << right_stack.front()->data << " is not symetric" << endl;
            return false;
        }

        return true;
    }

    void test() {
        shared_ptr<Node<int>> root = 
            N(314, N(6, nullptr , N(2, nullptr, N(3)) ), N(6, N(2, N(3), nullptr), nullptr));
        bool is = is_symetric(root);
        cout << "is_symetric: " << (is? "true": "false") << endl;

        root = 
            N(314, N(6, nullptr , N(561, nullptr, N(3)) ), N(6, N(561), nullptr));
        is = is_symetric(root);    
        cout << "is_symetric: " << (is? "true": "false") << endl;
        
    }
}

void test_p9_2_check_symetric() {
    PRINT_FUNC_NAME;
    p9_2::test();
}