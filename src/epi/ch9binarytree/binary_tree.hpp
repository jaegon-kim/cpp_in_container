#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
    struct Node {
        Node(T v) : data(v) {}
        T data;
        size_t num_child = 0;
        shared_ptr<Node<T>> left = nullptr;
        shared_ptr<Node<T>> right = nullptr;
        shared_ptr<Node<T>> parent = nullptr;
    };


#endif // __BINARY_TREE_H__