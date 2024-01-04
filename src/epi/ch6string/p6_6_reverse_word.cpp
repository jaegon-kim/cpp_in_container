#include <iostream>
#include <deque>
#include <string>
#include "utility/dump.hpp"

using namespace std;

namespace p6_6 {

    string reverse_word(const string & s) {
        deque<string> q(0);
        size_t len = s.length();
        string w = "";
        for (size_t i = 0; i < len; i++) {
            char c = s[i];
            switch(c) {
                case ' ':
                    if (w.length()) {
                        q.push_front(w);
                        w = "";
                    }                     
                    q.push_front(" ");
                    break;
                default:
                    w.push_back(c);
                    break;
            }
        }

        if (w.length()) {
            q.push_front(w);
        }

        string reverse_word = "";        
        size_t q_len = q.size();
        for(size_t i = 0; i < q_len; i++) {
            reverse_word.append(q[i]);
        }

        return reverse_word;
    }

    void test(const string & s) {
        cout <<"'" << s << "' -> '" << reverse_word(s) << "'" << endl;
    } 
}


void test_p6_6_reverse_word() {
    PRINT_FUNC_NAME;
    p6_6::test("");
    p6_6::test("Alice");
    p6_6::test("Alice likes Bob");
    p6_6::test("Alice likes Bob very much");
}