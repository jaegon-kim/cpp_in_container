#include <iostream>
#include <memory>
#include "utility/dump.hpp"

using namespace std;

namespace p7_0 {

    template <typename T>
    struct Node {
        Node(T & v) : data(v), next(nullptr) {}
        ~Node() {
             cout << "Node destructed (data: ";
             cout << data << ")" << endl; 
        }

        T data;
        shared_ptr<Node<T>> next = nullptr;
    };

    template <typename T>
    class LinkedList {

        public:
            LinkedList() : head(nullptr), tail(nullptr) {}

            void push_back(T v) {
                cout << "push " << v << endl;

                // make_shared: heap allocation
                shared_ptr<Node<T>> node = make_shared<Node<T>>(v);
                if (head == nullptr) {
                    head = node;
                    tail = node;
                    return;
                }
                tail->next = node;
                tail = node;
            }

            void pop_head() {
                if (head == nullptr) {
                    return;
                }
                if (head == tail) {
                    tail = nullptr;
                    head = nullptr;
                    return;
                }
                // auto free by removing reference
                head = head->next;
            }

            void dump() {
                shared_ptr<Node<T>> node = head;
                while(node->next != nullptr) {
                    cout << node->data << ", ";
                    node = node->next;
                }
                cout << node->data << endl;
            }

        private:
            void insert(shared_ptr<Node<T>> & prev_node, shared_ptr<Node<T>> & node) {
                node.next = prev_node.next;
                prev_node.next = node;
            }

            shared_ptr<Node<T>> head;
            shared_ptr<Node<T>> tail;
    };



    void test() {
        LinkedList<int> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.pop_head();
        l.push_back(4);
        l.dump();
    }


}


void test_p7_0_linked_list() {
    PRINT_FUNC_NAME;
    p7_0::test();
}