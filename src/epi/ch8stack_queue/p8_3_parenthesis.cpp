#include <iostream>
#include <string>
#include <list>

#include "utility/dump.hpp"

using namespace std;

namespace p8_3 {

    bool is_valid_parenthesis(const string & str) {
        list<char> l;
        size_t len = str.size();
        for(size_t i = 0; i < len; i++) {
            char c = str[i];
            switch(c) {
                case '(':
                case '[':
                case '{':
                    l.push_front(c);
                    break;
                case ')':
                    if (l.front() == '(') {
                        l.pop_front();
                    } else {
                        return false;
                    }
                    break;                    
                case ']':
                    if (l.front() == '[') {
                        l.pop_front();
                    } else {
                        return false;
                    }
                    break;                    
                case '}':
                    if (l.front() == '{') {
                        l.pop_front();
                    } else {
                        return false;
                    }
                    break;
            }          
        }

        return (l.size() == 0);
    }

    void test(const string & str, bool expect) {
        bool valid = is_valid_parenthesis(str);
        cout << str << (valid? " is valid ": " is not valid ")
             << (is_valid_parenthesis(str) == expect? "[sucess]": "[failure]") << endl;
    }
}

void test_p8_3_parenthesis() {
    PRINT_FUNC_NAME;

    p8_3::test("([]){()}", true);
    p8_3::test("[()[]{()()}]", true);
    p8_3::test("[)]", false);
    p8_3::test("[([]{()()}]", false);

}
