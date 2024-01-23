#include <iostream>
#include <bitset>
#include "binary_tree.hpp"
#include "utility/dump.hpp"

using namespace std;

namespace p9_5 {

    using node_ptr = shared_ptr<Node<unsigned long long>>;

    node_ptr N(unsigned long long v) {
        node_ptr new_node = make_shared<Node<unsigned long long>>(v);
        return new_node;
    }

    node_ptr N(unsigned long long v, node_ptr left, node_ptr right) {
        node_ptr new_node = make_shared<Node<unsigned long long>>(v);
        new_node->left = left;
        new_node->right = right;
        return new_node;
    }
    
    unsigned long long traverse(node_ptr node, unsigned long long v) {
        unsigned long long sum = 0;
        if (!node) {
            return 0;
        }
        v <<= 1;
        v += node->data;
        if (!node->left && !node->right) {
            sum += v;
            cout << bitset<64>(v) << ", sum=" << sum << endl;           
        } else {
            sum += traverse(node->left, v);
            sum += traverse(node->right, v);       
        }
        v >>= 1;
        return sum;       
    }

    void test() {
        node_ptr root = 
        N(1, N(0, N(0, N(0), N(1)), N(1, nullptr, N(1, N(0), nullptr))) , N(1, N(0, nullptr, N(0, N(1, nullptr, N(1)), N(0))) , N(0, nullptr, N(0))));

        cout << traverse(root, 0) << endl;
    }
}

void test_p9_5_path_bit_sum() {
    PRINT_FUNC_NAME;
    p9_5::test();
}