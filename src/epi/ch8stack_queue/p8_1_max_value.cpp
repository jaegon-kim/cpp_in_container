#include <iostream>
#include <memory>
#include <vector>
#include <optional>

#include "utility/dump.hpp"
#include "epi/ch7linkedlist/linked_list.hpp"

using namespace std;
using namespace p7;

namespace p8_1 {

    void test(const vector<int> & v) {
        LinkedList<int> s;
        size_t len = v.size();
        for (size_t i = 0; i < len; i++) {
            s.push_front(v[i]);
            cout << "push: " << v[i] << ", max: " << s.get_max().value() << endl;
        }

        for (size_t i = 0; i < len; i++) {
            cout << "pop: " << s.pop_front().value_or(-1) << ", max: " << s.get_max().value_or(-1) << endl;
        }

    }
}

void test_p8_1_max_value() {
    PRINT_FUNC_NAME;
    p8_1::test(vector<int> { 5, 3, 2, 6, 1, 3, 8, 0});
}