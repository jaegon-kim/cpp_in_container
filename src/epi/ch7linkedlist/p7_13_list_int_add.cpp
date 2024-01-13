#include <iostream>
#include <vector>
#include <memory>
#include <optional>

#include <utility/dump.hpp>
#include "linked_list.hpp"

using namespace std;
using namespace p7;

namespace p7_13 {

    LinkedList<int> list_int_add(LinkedList<int> & l1, LinkedList<int> & l2) {

        LinkedList<int> rslt;
        int carry = 0;
        while(!l1.is_empty() && !l2.is_empty()) {
            int v1 = l1.pop_front().value();
            int v2 = l2.pop_front().value();
            int sum = v1 + v2 + carry;
            carry = sum / 10;
            rslt.push_back(sum % 10);
        }

        if (!l1.is_empty()) {
            while(!l1.is_empty()) {
                int v1 = l1.pop_front().value() + carry;
                carry = v1 / 10;
                rslt.push_back(v1 % 10);
            }
        } else {
            while(!l2.is_empty()) {
                int v2 = l2.pop_front().value() + carry;
                carry = v2 / 10;
                rslt.push_back(v2 % 10);
            }
        }

        if (carry) {
            rslt.push_back(carry);
        }
        return rslt;
    }

    void test(const vector<int> & num1, const vector<int> & num2) {
        LinkedList<int> l1 = v2l(num1);
        LinkedList<int> l2 = v2l(num2);

        l1.dump(false);
        cout << " + ";
        l2.dump(false);
        cout << " = ";

        LinkedList<int> rslt = list_int_add(l1, l2);        
        rslt.dump(true);
    }
}


void test_p7_13_list_int_add() {
    PRINT_FUNC_NAME;
    // 413 + 907 = 1320
    p7_13::test(vector<int>{3, 1, 4}, vector<int>{7, 0, 9});
}