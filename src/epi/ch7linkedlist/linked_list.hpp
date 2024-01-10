#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <iostream>
#include <memory>
#include <vector>
#include <utility>

namespace p7 {

    template <typename T>
    struct Node {
        Node(T v) : data(v) {}
        T data;
        std::shared_ptr<Node<T>> next = nullptr;
    };

    template <typename T>
    class LinkedList {
        public:
            void push_back(T v) {
                std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(v);
                if (!head) {
                    head = new_node;
                    tail = new_node;
                    len++;
                    return;
                }
                tail->next = new_node;
                tail = new_node;
                len++;
                return;
            }

            std::shared_ptr<Node<T>> get_node(size_t pos) {
                std::shared_ptr<Node<T>> node = head;
                size_t p = 0;
                while(p < pos) {
                    node = node->next;
                    p++;
                }
                return node; 
            }

            void link(LinkedList<T> & l, size_t link_pos) {
                std::shared_ptr<Node<T>> node = get_node(link_pos);
                l.get_tail()->next = node;
                l.set_tail(tail);

                size_t additional_len = l.last_length(node);
                //std::cout << "additional_len: " << additional_len << std::endl;
                l.set_size(l.size() + additional_len);
            }

            bool is_overlap(LinkedList<T> & l) {
                return (tail == l.get_tail());
            }

            std::shared_ptr<Node<T>> get_linked_node(LinkedList<T> & l) {
                std::shared_ptr<Node<T>> this_node;
                std::shared_ptr<Node<T>> l_node;

                if (size() > l.size()) {
                    int this_start = size() - l.size();
                    this_node = get_node(this_start);
                    l_node = l.get_head();
                } else {
                    int l_start = l.size() - size();
                    this_node = head;
                    l_node = l.get_node(l_start);
                }

                while(this_node != l_node) {
                    this_node = this_node->next;
                    l_node = l_node->next;
                }
                
                return this_node;
            }

            std::shared_ptr<Node<T>> get_linked_node(LinkedList<T> & l, std::shared_ptr<Node<T>> tail) {
                std::shared_ptr<Node<T>> this_node = head;
                size_t this_size = 1;
                while(this_node != tail) {
                    this_node = this_node->next;
                    this_size++;
                }
                std::shared_ptr<Node<T>> l_node = l.get_head();
                size_t l_size = 1;
                while(l_node != tail) {
                    l_node = l_node->next;
                    l_size++;
                }

                //std::cout << "this_size: " << this_size << std::endl;
                //std::cout << "l_size: " << l_size << std::endl;

                if (this_size > l_size) {
                    int this_start = this_size - l_size;
                    this_node = get_node(this_start);
                    l_node = l.get_head();
                } else {
                    int l_start = l_size - this_size;
                    this_node = head;
                    l_node = l.get_node(l_start);
                }

                while(this_node != l_node) {
                    this_node = this_node->next;
                    l_node = l_node->next;
                }
                
                return this_node;
            }



            size_t last_length(std::shared_ptr<Node<T>> node) {
                size_t len = 1;
                while(node != tail) {
                    node = node->next;
                    len++;
                }
                return len;
            }

            void set_cycle(size_t target_idx, size_t source_idx) {
                size_t cnt = 0;
                std::shared_ptr<Node<T>> target = head;
                std::shared_ptr<Node<T>> source;

                while(cnt < target_idx) {
                    target = target->next;
                    cnt++;
                }
                //cout << cnt << ", " << target->data << ", " << target.use_count() << endl;
                source = target;
                while(cnt < source_idx) {
                    source = source->next;
                    cnt++;
                }
                //cout << cnt << ", " << source->data << endl;
                source->next = target;
            }

            std::pair<std::shared_ptr<Node<T>>, size_t> find_cycle() {
                std::shared_ptr<Node<T>> tortoise = head;
                std::shared_ptr<Node<T>> hare = head;

                while (true) {
                    if (!tortoise->next) {
                        return std::make_pair(nullptr, 0);
                    }
                    if (!hare->next || !hare->next->next) {
                        return std::make_pair(nullptr, 0);
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
                        return std::make_pair(hare, cycle_len);
                    }
                }
            }

            size_t size() {
                return len;
            }

            void set_size(size_t s) {
                len = s;
            }

            std::shared_ptr<Node<T>> get_head() {
                return head;
            }

            std::shared_ptr<Node<T>> get_tail() {
                return tail;
            }

            void set_tail(std::shared_ptr<Node<T>> node) {
                tail = node;
            }

            void dump(bool nl) {
                std::cout << "len: " << len <<" {";
                std::shared_ptr<Node<T>> node = head;
                size_t cnt = 0;
                while(node->next && cnt++ < 30) {
                    std::cout << node->data << ", ";
                    node = node->next;                    
                }
                std::cout << node->data << "}";
                if (nl) {
                    std::cout << std::endl;
                }
            }

        private:
            size_t len = 0;
            std::shared_ptr<Node<T>> head = nullptr;
            std::shared_ptr<Node<T>> tail = nullptr;
    };

    template<typename T>
    LinkedList<T> v2l(const std::vector<T> & v) {
        size_t len = v.size();
        LinkedList<T> l;
        for(size_t i = 0; i < len; i++) {
            l.push_back(v[i]);
        }
        return l;
    }
}

#endif // __LINKED_LIST_HPP__

