#include <iostream>
#include <memory>
#include <unordered_map>
#include <deque>
#include "utility/dump.hpp"

using namespace std;

namespace p8_6 {

    template<typename T>
    struct Node {
        Node(T v) : data(v) {}
        T data;
        shared_ptr<Node<T>> left = nullptr;
        shared_ptr<Node<T>> right = nullptr;
    };

    template<typename T>
    shared_ptr<Node<int>> n(T v) {
        shared_ptr<Node<int>> node = make_shared<Node<int>>(v);
        return node;
    }

    template<typename T>
    shared_ptr<Node<int>> n(T v, shared_ptr<Node<int>> left, shared_ptr<Node<int>> right) {
        shared_ptr<Node<int>> node = make_shared<Node<int>>(v);
        node->left = left;
        node->right = right;
        return node;
    }

    template<typename T>
    void traverse(shared_ptr<Node<T>> node, int depth, unordered_map<int, deque<T>> & map) {
        if (!node) {
            return;
        }
        if (map.find(depth) == map.end()) {
            map[depth] = deque<T>();
        }
        map[depth].emplace_back(node->data);
        cout << node->data << ", ";
        traverse(node->left, depth + 1, map);
        traverse(node->right, depth + 1, map);
    }

    void test() {
        shared_ptr<Node<int>> root = 
            n(314, n(6, n(271, n(28), n(0)), n(561, nullptr , n(3, nullptr, n(7)))), n(6, n(2, n(1, n(401, nullptr, n(641)), n(257)), nullptr), n(274, nullptr, n(28))));
        
        unordered_map<int, deque<int>> map;
        traverse<int>(root, 0, map);
        cout << endl;

        for(int i = 0; true; i++) {
            if (map.find(i) == map.end()) {
                break;
            }
            dump_deq(map[i], false);
            cout << endl;
        }        
    }
}

void test_p8_6_tree_level() {
    PRINT_FUNC_NAME;
    p8_6::test();
    
}