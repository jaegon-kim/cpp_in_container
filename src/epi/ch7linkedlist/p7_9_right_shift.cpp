#include <iostream>
#include <vector>
#include <memory>

#include "utility/dump.hpp"

using namespace std;

namespace p7_9 {

    template <typename T>
    struct Node {
        Node(T v) : data(v) {}
        T data;
        shared_ptr<Node<T>> next = nullptr;
    };

    template <typename T>
    class LinkedList {
        public:
            void push_sorted(T v) {
                shared_ptr<Node<T>> new_node = make_shared<Node<T>>(v);
                if (!head) {
                    head = new_node;
                    tail = new_node;
                    tail->next = head;
                    return;
                }

                if (v < head->data) {
                    new_node->next = head;
                    head = new_node;
                    tail->next = head;
                    return;
                }

                shared_ptr<Node<T>> last_smaller = head;

                while(true) {
                    if (last_smaller == tail) {
                        last_smaller->next = new_node;
                        tail = new_node;
                        tail->next = head;
                        return;
                    }
                    if (v < last_smaller->next->data) {
                        new_node->next = last_smaller->next;
                        last_smaller->next = new_node;
                        return;
                    }
                    last_smaller = last_smaller->next;
                }
            }

            void shift_right(const int shift_cnt) {
                if (!head) {
                    return;
                }
                int cnt = 0;
                while(cnt < shift_cnt) {
                    head = head->next;
                    tail = tail->next;
                    cnt++;
                }
            }

            void dump(bool nl) {
                std::cout << " {";
                std::shared_ptr<Node<T>> node = head;
                size_t cnt = 0;
                if (node) {
                    while(node != tail && cnt++ < 30) {
                        std::cout << node->data << ", ";
                        node = node->next;                    
                    }
                    std::cout << node->data;
                }
                std::cout << "}";
                if (nl) {
                    std::cout << std::endl;
                }
            }

        private:
            shared_ptr<Node<T>> head = nullptr;
            shared_ptr<Node<T>> tail = nullptr;
    };

    template<typename T>
    LinkedList<T> v2l_sorted(const std::vector<T> &v) {
        size_t len = v.size();
        LinkedList<T> l;
        for(size_t i = 0; i < len; i++) {
            l.push_sorted(v[i]);
        }
        return l;
    }


    void test(const vector<int> & v, int shift_cnt) {
        dump_vec<int>(v, false);
        LinkedList<int> l = v2l_sorted<int>(v);
        cout << " -> ";
        l.dump(false);
        l.shift_right(shift_cnt);
        cout << " -(>>" << shift_cnt << ")> ";
        l.dump(true);
    }

}

void test_p7_9_right_shift() {
    PRINT_FUNC_NAME;
    p7_9::test(vector<int> {0}, 5);
    p7_9::test(vector<int> {0, 0}, 5);
    p7_9::test(vector<int> {3, 4, 6, 1, 2, 9, 1, 3, 5, 6}, 1);
    p7_9::test(vector<int> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 2);
    p7_9::test(vector<int> {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 3);
    p7_9::test(vector<int> {9, 1, 3, 4, 5, 4, 3, 2, 1, 0}, 4);
    p7_9::test(vector<int> {9, 9, 3, 4, 5, 4, 3, 4, 1, 0}, 5);
    p7_9::test(vector<int> {9, 9, 3, 4, 5, 4, 0, 0, 1, 0}, 6);

}