#include <iostream>
#include <memory>
#include <vector>
#include <optional>

#include "utility/dump.hpp"

using namespace std;

namespace p7_2 {

    template <typename T>
    struct Node {
        Node(T t) : data(t) {}

        T data;
        shared_ptr<Node<T>> next = nullptr;
    };

    template <typename T>
    class LinkedList {
        public:
            void push_back(T t) {
                shared_ptr<Node<T>> new_node = make_shared<Node<T>>(t);
                if (head == nullptr) {
                    head = new_node;
                    tail = new_node;
                    return;
                }
                tail->next = new_node;
                tail = new_node;
                return;
            }

            void push_front(T t) {
                shared_ptr<Node<T>> new_node = make_shared<Node<T>>(t);
                if (head == nullptr) {
                    head = new_node;
                    tail = new_node;
                    return;
                }
                new_node->next = head;
                head = new_node;
                return;
            }

            optional<T> front() {
                if (head == nullptr) {
                    return nullopt;
                }
            }

            optional<T> pop_front() {
                if (head == nullptr) {
                    return nullopt;
                }
                shared_ptr<Node<T>> node = head;
                head = head->next;
                node->next = nullptr;
                return node->data;
            }

            void dump(bool nl) {
                shared_ptr<Node<T>> node = head;
                if (node == nullptr) {
                    return;
                }
                while(node->next != nullptr) {
                    cout << node->data << ", ";
                     node = node->next;
                }
                cout << node->data;
                if (nl) {
                    cout << endl;
                }
                return;
            }

            void reverse_with_value(int s, int e) {
                LinkedList<T> l;
                
                if (head == nullptr) {
                    return;
                }
                shared_ptr<Node<T>> node = head;
                int c = 0;
                while (node != nullptr && c <= e) {
                    if (c >= s) {
                        l.push_front(node->data);
                    }
                    node = node->next;
                    c++;
                }

                node = head;
                c = 0;
                while (node != nullptr && c <= e) {
                    if (c >= s) {
                        node->data = l.pop_front().value();
                    }
                    node = node->next;
                    c++;
                }
            }

           void reverse_with_node(int s, int e) {
                shared_ptr<Node<T>> prior = nullptr;
                shared_ptr<Node<T>> node;
                shared_ptr<Node<T>> post = nullptr;

                int c = 0;
                if (s > 0) {
                    c = 1;
                    prior = head;
                    while(c < s) {
                        prior = prior->next;
                        c++;
                    }
                    node = prior->next;
                    if (node == nullptr) {
                        return;
                    }
                } else {
                    node = head;
                    // prior will be nullptr
                }

                if (node->next) {
                    post = recursive_reverse(c + 1, e, node->next, prior);
                    node->next->next = node;
                }

                if (post) {
                    node->next = post;
                } else {
                    // node is the last node
                    tail = node;
                    node->next = nullptr;
                }
            }

            shared_ptr<Node<T>> recursive_reverse(
                int curr, int end, shared_ptr<Node<T>> curr_node, // this is not null
                shared_ptr<Node<T>> & prior_node
            ) {
                shared_ptr<Node<T>> post_node = nullptr;
                if (curr == end) { // curr_node reached to end
                    if (prior_node) {
                        prior_node->next = curr_node;
                    } else { // prior_node is null, curr_node will be head
                        head = curr_node;
                    }
                    post_node = curr_node->next; // post_node can have node or null
                    return post_node;
                } 

                // if curr is not reached to end, curr_node->next always has node
                post_node = recursive_reverse(curr + 1, end, curr_node->next, prior_node);
                curr_node->next->next = curr_node;
                return post_node;
            }


        private:
            shared_ptr<Node<T>> head = nullptr;
            shared_ptr<Node<T>> tail = nullptr;
    };


    void test(const vector<int> & v, int start_idx, int end_idx) {
        LinkedList<int> l;
        size_t len = v.size();
        for (size_t i = 0; i < len; i++) {
            l.push_back(v[i]);
        }
        //l.dump(false);
        // start_idx, and end_idx always should be in bound 
        l.reverse_with_node(start_idx, end_idx);
        cout << " -(" << start_idx << " ~ " << end_idx <<")-> ";
        l.dump(true);
    }

}


void test_p7_2_reverse_linked_list() {
    PRINT_FUNC_NAME;
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0, 9);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0, 1);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0, 2);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0, 3);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 8, 9);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 7, 9);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 6, 9);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 5, 9);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 1, 8);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 2, 7);
    p7_2::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 6);

}