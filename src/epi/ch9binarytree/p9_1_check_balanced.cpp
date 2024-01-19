#include <iostream>
#include <memory>
#include "utility/dump.hpp"

using namespace std;

namespace p9_1 {

    template <typename T>
    struct Node {
        Node(T v) : data(v) {
            //cout << "Node " << data << " is created" << endl;
        }
        ~Node() {
            //cout << "Node " << data << " is freed" << endl;
        }
        T data;
        // Binary Tree를 unique_ptr로 쓰는건 좀 아니다....
        unique_ptr<Node<T>> left = nullptr;
        unique_ptr<Node<T>> right = nullptr;
    };

    template <typename T>
    unique_ptr<Node<T>> N(T v) {
        unique_ptr<Node<T>> new_node = make_unique<Node<T>>(v);
        //cout << "return N" << endl;
        return new_node;
    }


    template <typename T>
    unique_ptr<Node<T>> N(T v, unique_ptr<Node<T>> left, unique_ptr<Node<T>> right) {
        unique_ptr<Node<T>> new_node = make_unique<Node<T>>(v);
        if (left -> data) {
            new_node->left = move(left);
        }
        if (right -> data) {
            new_node->right = move(right);
        }
        //cout << "return N" << endl;
        return new_node;
    }

    int abs(int a, int b) {
        if (a > b) {
            return a - b;
        } else {
            return b - a;
        }
    }

    template <typename T>
    int traverse(unique_ptr<Node<T>> node) {
        if (node == nullptr) {
            return 0;
        }

        cout << node->data << ", ";

        int left_depth = traverse(move(node->left));
        if (left_depth == - 1) {
            return -1;
        }

        int right_depth = traverse(move(node->right));
        if (right_depth == - 1) {
            return -1;
        }

        if (abs(left_depth, right_depth) > 1) {
            cout << "unbalanced node " << node->data << endl;
            return -1;
        }

        if (left_depth > right_depth) {
            return left_depth + 1;
        } else {
            return right_depth + 1;
        }
    }

    void test() {
        unique_ptr<Node<char>> root = 
            //N('A', N('B', N('C', N('D', N('E'), N('F')) , N('G')), N('H', N('I'), N('J'))) , 
            N('A', N('B', N('C', N('D', N('E'), N('F')) , N((char)0)), N('H', N('I'), N('J'))) , 
            N('K', N('L', N('M'), N('N')), N('O')));
        cout << "return test" << endl;

        if (traverse(move(root)) == -1) {
            cout << "[unbalanced]" << endl;
        } else {
            cout << "[balanced]" << endl;
        }
        // root가 reference를 잃어 버림.
        // unique_ptr을 쓰는 건 좀 아닌 듯함.
        traverse(move(root));

        
    }
}

void test_p9_1_check_balanced() {
    PRINT_FUNC_NAME;
    p9_1::test();
}