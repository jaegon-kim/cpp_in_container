#ifndef __UTILITY_DUMP_HPP__
#define __UTILITY_DUMP_HPP__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <list>

#define PRINT_FUNC_NAME { std::cout << " * " << __func__ << std::endl; }

template <typename T>
void dump_vec(const std::vector<T> & v, bool nl) {
    std::cout << "{";
    size_t len = v.size();
    for (size_t i = 0; i < len; i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}

template <typename T>
void dump_list(const std::list<T> & l, bool nl) {
    std::cout << "{";
    for (auto &v: l) {
        std::cout << v << ", ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}

template <typename T>
void dump_deq(const std::deque<T> & q, bool nl) {
    std::cout << "{";
    size_t len = q.size();
    for (size_t i = 0; i < len; i++) {
        std::cout << q[i] << ", ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}


template <typename K, typename V>
void dump_map(const std::unordered_map<K, V> & m, bool nl) {
    std::cout << "{";
    for (std::pair<K, V> p: m) {
        std::cout << "(" << p.first << " ," << p.second << "), ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}



#endif // __UTILITY_DUMP_HPP__