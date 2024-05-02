#include <iostream>
#include "utility/dump.hpp"
#include <memory>

using namespace std;

namespace p15_09 {

    template <typename T>
    struct Node {
        Node(T d) : data{d} {}

        shared_ptr<Node<T>> left = nullptr;
        shared_ptr<Node<T>> right = nullptr;
        T data;
    };

    template <typename T>
    void traverse(shared_ptr<Node<T>> n_ptr) {
        if (n_ptr == nullptr) {
            return;
        }
        cout << n_ptr->data << "(";
        if (n_ptr->left) {
            cout << n_ptr->left->data;
        }
        cout << ", ";
        if (n_ptr->right) {
            cout << n_ptr->right->data;
        }
        cout << "), ";

        traverse(n_ptr->left);
        traverse(n_ptr->right);
    }

    template <typename T>
    void gen(shared_ptr<Node<T>> n_ptr, size_t s, shared_ptr<Node<T>> r_ptr) {
        if (!s) {
            traverse(r_ptr);
            cout << endl;
            return;
        }

        shared_ptr<Node<T>> new_ptr = make_shared<Node<T>>(s);

        n_ptr->left = new_ptr;
        gen(new_ptr, s - 1, r_ptr);
        n_ptr->left = nullptr;

        n_ptr->right = new_ptr;
        gen(new_ptr, s - 1, r_ptr);
        n_ptr->right = nullptr;

        if (s >= 2) {
            n_ptr->left = new_ptr;
            n_ptr->right = make_shared<Node<T>>(s - 1);
            if ((s - 2) > 0) {
                gen(n_ptr->left, s - 2, r_ptr);
                gen(n_ptr->right, s - 2, r_ptr);
            } else {
                traverse(r_ptr);
                cout << endl;
            }
            n_ptr->left = nullptr;
            n_ptr->right = nullptr;
        }
    }

    void test(size_t n) {
        shared_ptr<Node<int>> r_ptr = make_shared<Node<int>>(n);
        gen(r_ptr, n - 1, r_ptr);
    }
}

void test_p15_09_gen_binarytree() {
    PRINT_FUNC_NAME;
    p15_09::test(4);
}