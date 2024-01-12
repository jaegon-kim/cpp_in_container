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
        ~Node() {
            //std::cout << "node(data:" << data << ") is deleted" << std::endl;
        }
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

            void push_back(std::shared_ptr<Node<T>> new_node) {
                if (!head) {
                    head = new_node;
                    tail = new_node;
                    new_node->next = nullptr;
                    len++;
                    return;
                }
                tail->next = new_node;
                tail = new_node;
                tail->next = nullptr;
                len++;
                return;
            }

            void push_sorted(T v) {
                std::shared_ptr<Node<T>> new_node = std::make_shared<Node<T>>(v);
                //dump(true);
                //std::cout << " adding: " << v << std::endl;
                if (!head) {
                    head = new_node;
                    tail = new_node;
                    len++;
                    return;
                }

                if (v < head->data) {
                    new_node->next = head;
                    head = new_node;
                    len++;
                    return;
                }
                std::shared_ptr<Node<T>> ls_node = head; // ls_node is not null, head is already last smaller
                while (true) {
                    if (!ls_node->next) {
                        break; // ls_node is tail
                    }
                    if ( v < ls_node->next->data) {
                        break;
                    }
                    ls_node = ls_node->next;
                }

                new_node->next = ls_node->next;
                ls_node->next = new_node;
                if (ls_node == tail) {
                    tail = new_node;
                }
                len++;
            }

            void delete_from_last(const int del_pos_from_last) {
                int k = 1;
                std::shared_ptr<Node<T>> k_node = head;
                while (k < del_pos_from_last && k_node) {
                    k++;
                    k_node = k_node->next;
                }
                if (!k_node) {
                    return;
                }

                std::shared_ptr<Node<T>> prev_node = nullptr;
                std::shared_ptr<Node<T>> del_node = head;
                while(k_node != tail) {
                    k_node = k_node->next;
                    prev_node = del_node;
                    del_node = del_node->next;
                }

                delete_node(prev_node, del_node);
            }

            void delete_node(std::shared_ptr<Node<T>> prev_node, std::shared_ptr<Node<T>> del_node) {

                if (del_node == head) { //prev_node may be null
                    head = del_node->next;
                } else {
                    prev_node->next = del_node->next;
                }

                if (del_node == tail) {
                    tail = prev_node;
                }
                len--;
            }

            void delete_non_last_node(std::shared_ptr<Node<T>> node) {
                if (node == tail && node->next) {
                    return;
                }
                if (node->next == tail) { 
                    tail = node; // CAUTION !! without this, tail node will not be deleted by shared_ptr
                }
                node->data = node->next->data;
                node->next = node->next->next;
                len--;
            }

            void remove_duplicated() {
                std::shared_ptr<Node<T>> dup_node = head;
                std::shared_ptr<Node<T>> node = head;

                if (!head) {
                    return;
                }
                int dup_cnt = 0;
                while(node) {
                    if (dup_node->data != node->data) {
                        dup_node->next = node;
                        dup_node = node;
                        len -= dup_cnt;
                        dup_cnt = 0;
                    } else {
                        dup_cnt++;
                    }
                    node = node->next;
                }
                if (dup_node->data == tail->data) {
                    dup_node->next = nullptr;
                    tail = dup_node;
                    len -= (dup_cnt - 1);
                }
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

            void even_odd_merge() {
                if (!head || !(head->next)) {
                    return;
                }

                LinkedList<T> odd_list;
                LinkedList<T> even_list;
                std::shared_ptr<Node<T>> odd = head;
                std::shared_ptr<Node<T>> even = head->next;

                while(true) {
                    odd_list.push_back(odd);                    
                    odd = even->next;

                    even_list.push_back(even);

                    if (!odd) {
                        break;
                    }

                    even = odd->next;

                    if (!even) {
                        break;
                    }                   
                }

                if (odd) {
                    odd_list.push_back(odd); 
                }

                if (even) {
                    even_list.push_back(even);
                }

                //std::cout << " odd "; odd_list.dump(true);
                //std::cout << " even "; even_list.dump(true);
                head = odd_list.get_head();
                odd_list.get_tail()->next = even_list.get_head();
                tail = even_list.get_tail();
            }

            void reverse_until_end(
                    std::shared_ptr<Node<T>> prior_node,
                    std::shared_ptr<Node<T>> node) {
                if (!node || node == tail) {
                    return;
                }

                if (!prior_node) { // node is head case
                    tail = node;
                } else {
                    prior_node->next = tail;
                    tail = node;
                }

                std::shared_ptr<Node<T>> prev_node = nullptr;
                std::shared_ptr<Node<T>> post_node = node->next;
                
                while(true) {
                    node->next = prev_node;
                    if (!post_node) {
                        break;
                    }
                    prev_node = node;
                    node = post_node;
                    post_node = post_node->next;
                }

                // node will be the last node
                if (!prior_node) {
                    head = node;
                }
            }

            bool is_palindrom() {

                if (head == tail) {
                    return true;
                }

                size_t pre_pos = len / 2 - 1;
                std::shared_ptr<Node<T>> prior_node = get_node(pre_pos);
                //std::cout << "pre_pos: " << prior_node->data << std::endl;

                reverse_until_end(prior_node, prior_node->next);
                //std::cout << " -> ";
                //dump(false);

                bool matched = true;
                std::shared_ptr<Node<T>> n1 = head;
                std::shared_ptr<Node<T>> n2 = prior_node -> next;

                for (size_t i = 0; i <= pre_pos; i++) {
                    if (n1->data != n2->data) {
                        matched = false;
                        break;
                    }

                    n1 = n1->next;
                    n2 = n2->next;
                }
                reverse_until_end(prior_node, prior_node->next);
                //std::cout << " -> ";
                //dump(false);

                return matched;
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
                if (node) {
                    while(node->next && cnt++ < 30) {
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

    template<typename T>
    LinkedList<T> v2l_sorted(const std::vector<T> &v) {
        size_t len = v.size();
        LinkedList<T> l;
        for(size_t i = 0; i < len; i++) {
            l.push_sorted(v[i]);
        }
        return l;
    }
}

#endif // __LINKED_LIST_HPP__

