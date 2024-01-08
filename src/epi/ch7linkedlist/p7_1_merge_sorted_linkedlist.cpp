#include <iostream>
#include <memory>
#include <optional>

#include "utility/dump.hpp"

using namespace std;

namespace p7_1 {

    template <typename T>
    struct Node {
        Node(T v) : data(v) {}
        ~Node() {
            //cout << "node destructed (data: " << data << ")" << endl;
        }

        T data;
        shared_ptr<Node<T>> next = nullptr;
    };

    template <typename T>
    class LinkedList {
        public:

            void push_back(T v) {
                //cout << "push " << v << endl;
                shared_ptr<Node<T>> new_node = make_shared<Node<T>>(v);
                if (head == nullptr) {
                    head = new_node;
                    tail = new_node;
                    return;
                }
                tail->next = new_node;
                tail = new_node;
            }

            optional<T> front() {
                if (head == nullptr) {
                    return nullopt;
                }
                return head->data;
            }

            optional<T> pop_front() {
                if (head == nullptr) {
                    return nullopt;
                }
                if (head == tail) {
                    tail = nullptr;
                }
                T v = head->data;
                head = head->next;
                return v;
            }

            bool is_empty() {
                if (head == nullptr) {
                    return true;
                } else {
                    return false;
                }
            }

            void dump() {
                shared_ptr<Node<T>> node = head;
                while(node != nullptr && node != tail) {
                    cout << node->data << ", ";
                    node = node->next;
                }
                if (node != nullptr) {
                    cout << node->data << endl;
                }
            }

        private:
            shared_ptr<Node<T>> head = nullptr;
            shared_ptr<Node<T>> tail = nullptr;
    };

    LinkedList<int> mere_sorted(LinkedList<int> & l1, LinkedList<int> &l2) {
        
        LinkedList<int> sorted_list;

        while(!l1.is_empty() && !l2.is_empty()) {
            if (l1.front() < l2.front()) {
                sorted_list.push_back(l1.pop_front().value());
            } else {
                sorted_list.push_back(l2.pop_front().value());
            }
        }

        while (!l1.is_empty()) {
                sorted_list.push_back(l1.pop_front().value());
        }

        while (!l2.is_empty()) {
                sorted_list.push_back(l2.pop_front().value());
        }

        return sorted_list;
    }


    void test() {

        LinkedList<int> l1;
        l1.push_back(1);
        l1.push_back(2);
        l1.push_back(5);
        l1.push_back(7);
        l1.pop_front();
        l1.dump();

        LinkedList<int> l2;
        l2.push_back(1);
        l2.push_back(3);
        l2.push_back(11);
        l2.pop_front();
        l2.dump();

        LinkedList<int> s = mere_sorted(l1, l2);
        s.dump();
    }

} 

void test_p7_1_merge_sorted_linkedlist() {
    PRINT_FUNC_NAME;
    p7_1::test();
}