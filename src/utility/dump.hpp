#ifndef __UTILITY_DUMP_HPP__
#define __UTILITY_DUMP_HPP__

#include <iostream>
#include <vector>

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



#endif // __UTILITY_DUMP_HPP__