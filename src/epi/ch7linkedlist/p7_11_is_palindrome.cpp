#include <iostream>
#include <vector>
#include <memory>

#include "utility/dump.hpp"
#include "linked_list.hpp"

using namespace std;
using namespace p7;

namespace p7_11 {

    template<typename T>
    void test(const vector<T> & v) {
        LinkedList<T> l = v2l<T>(v);
        l.dump(false);
        cout << (l.is_palindrom()? " is palindrome": " is not palindrome") << endl;
    }
}

void test_p7_11_is_palindrome() {
    PRINT_FUNC_NAME;
    p7_11::test(vector<int>{0});
    p7_11::test(vector<int>{0, 0});
    p7_11::test(vector<int>{0, 1});
    p7_11::test(vector<int>{0, 0, 0});
    p7_11::test(vector<int>{0, 0, 1});
    p7_11::test(vector<int>{0, 1, 0});
    p7_11::test(vector<int>{0, 1, 1, 0});
    p7_11::test(vector<int>{0, 1, 1, 1});
    p7_11::test(vector<int>{0, 1, 2, 1, 0});
    p7_11::test(vector<int>{0, 1, 2, 1, 1});
    p7_11::test(vector<char>{'a', 'b', 'c', 'b', 'a'});
    p7_11::test(vector<char>{'a', 'b', 'c', 'c', 'b', 'a'});
    p7_11::test(vector<char>{'a', 'b', 'c', 'e', 'c', 'b', 'a'});
    p7_11::test(vector<char>{'a', 'b', 'c', 'e', 'c', 'b', 'b'});

}