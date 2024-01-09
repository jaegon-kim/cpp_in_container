#include <iostream>
#include <memory>
#include <vector>
#include <utility>

#include "utility/dump.hpp"

using namespace std;

namespace p7_3 {

    template <typename T>
    struct Node {
        Node(T v) : data(v){}
        T data;
        shared_ptr<Node<T>> next = nullptr;
    };

    template <typename T>
    class LinkedList {
        public:
            void push_back(T v) {
                shared_ptr<Node<T>> new_node = make_shared<Node<T>>(v);
                if (!head) {
                    head = new_node, tail = new_node;
                    return;
                }
                tail->next = new_node;
                tail = new_node;
                return;
            }

            void set_cycle(size_t i, size_t j) {
                size_t cnt = 0;
                shared_ptr<Node<T>> target = head;
                shared_ptr<Node<T>> source;

                while(cnt < i) {
                    target = target->next;
                    cnt++;
                }
                //cout << cnt << ", " << target->data << ", " << target.use_count() << endl;
                source = target;
                while(cnt < j) {
                    source = source->next;
                    cnt++;
                }
                //cout << cnt << ", " << source->data << endl;
                source->next = target;
            }

            pair<shared_ptr<Node<T>>, size_t> find_cycle() {
                shared_ptr<Node<T>> tortoise = head;
                shared_ptr<Node<T>> hare = head;

                while (true) {
                    if (!tortoise->next) {
                        return make_pair(nullptr, 0);
                    }
                    if (!hare->next || !hare->next->next) {
                        return make_pair(nullptr, 0);
                    }
                    tortoise = tortoise->next;
                    hare = hare->next->next;

                    if (tortoise == hare) {
                        //cout << "found cycle at " << tortoise->data << endl;

                        hare = head;
                        while (tortoise != hare) {
                            tortoise = tortoise->next;
                            hare = hare->next;
                        }
                        //cout << "found cycle start at " << tortoise->data << endl;

                        int cycle_len = 1;
                        tortoise = tortoise->next;
                        while(tortoise != hare) {
                            tortoise = tortoise->next;
                            cycle_len++;
                        }
                        //cout << "found cycle len: " << cycle_len << endl;
                        return make_pair(hare, cycle_len);
                    }
                }
            }

            void dump(bool nl) {
                cout << "{";
                shared_ptr<Node<T>> node = head;
                size_t cnt = 0;
                while(node->next && cnt++ < 50) {
                    cout << node->data << ", ";
                    node = node->next;                    
                }
                cout << node->data << "}";
                if (nl) {
                    cout << endl;
                }
            }

        private:
            shared_ptr<Node<T>> head = nullptr;
            shared_ptr<Node<T>> tail = nullptr;
    };

    void test(const vector<int> & v, size_t source, size_t target) {
        size_t len = v.size();
        LinkedList<int> l;
        for(size_t i = 0; i < len; i++) {
            l.push_back(v[i]);
        }
        l.dump(false);
        cout << " set cycle " << source << " -> " << target << endl;
        l.set_cycle(source, target);
        //l.dump(true);
        pair<shared_ptr<Node<int>>, size_t> p = l.find_cycle();
        if (!p.first) {
            cout << " - no cycle" << endl;
        } else {
            cout << " - cycle start: " << p.first->data << ", len: " << p.second << endl;
        }
    }
}

// Floyd's Tortoise & Hare Algorithm
void test_p7_3_cycle_detect() {
    PRINT_FUNC_NAME;
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7}, 2, 5);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7}, 0, 5);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7}, 0, 0);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7}, 1, 1);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 4, 6);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 3, 6);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 6);
    p7_3::test(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4, 6);
}

