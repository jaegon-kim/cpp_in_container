#ifndef __UTILITY_DUMP_HPP__
#define __UTILITY_DUMP_HPP__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
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
void dump_vec(const std::vector<T> & v, size_t start_idx, size_t end_idx, bool nl) {
    std::cout << "{";
    for (size_t i = start_idx; i <= end_idx; i++) {
        std::cout << v[i] << ", ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}

template <typename T>
void dump_vec_with_idx(const std::vector<T> & v, bool nl) {
    std::cout << "{";
    size_t len = v.size();
    for (size_t i = 0; i < len; i++) {
        std::cout << "[" << i << "]" << v[i] << ", ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}


template <typename F, typename S>
void dump_vec_of_pair(const std::vector<std::pair<F, S>> & v, bool nl) {
    std::cout << "{";
    size_t len = v.size();
    for (size_t i = 0; i < len; i++) {
        std::cout << "(" << v[i].first << ", " << v[i].second << "), ";
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



template <typename F, typename S>
void dump_list_of_pair(const std::list<std::pair<F, S>> & l, bool nl) {
    std::cout << "{";
    for (auto & p: l) {
        std::cout << "(" << p.first << ", " << p.second << "), ";

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
    for (const std::pair<K, V> & p: m) {
        std::cout << "(" << p.first << " ," << p.second << "), ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}

template <typename K, typename V>
void dump_map(const std::map<K, V> & m, bool nl) {
    std::cout << "{";
    for (const auto & p: m) {
        std::cout << "(" << p.first << " ," << p.second << "), ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }
}


template <typename T>
void dump_set(const std::unordered_set<T> & s, bool nl) {
    std::cout << "{";
    for (const T & e: s) {
        std::cout << "(" << e << "), ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }

}


template <typename T>
void dump_set(const std::set<T> & s, bool nl) {
    std::cout << "{";
    for (const T & e: s) {
        std::cout << "(" << e << "), ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }

}


template <typename T>
void dump_set_of_pair(const std::set<T> & s, bool nl) {
    std::cout << "{";
    for (const T & e: s) {
        std::cout << "(" << e.first << ", " << e.second << "), ";
    }
    std::cout << "}";
    if (nl) {
        std::cout << std::endl;
    }

}


template <typename T>
void dump_vec_of_unoreded_set(const std::vector<std::unordered_set<T>> & v_s) {
    for (auto s: v_s) {
        dump_set(s, true);
    }
}

template <typename T>
void dump_vec_of_vec(const std::vector<std::vector<T>> & v_v) {
    for (auto v: v_v) {
        dump_vec(v, true);
    }
}


#endif // __UTILITY_DUMP_HPP__