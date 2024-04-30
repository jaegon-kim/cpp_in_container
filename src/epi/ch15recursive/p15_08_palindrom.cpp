#include <iostream>
#include "utility/dump.hpp"
#include <list>
#include <vector>

using namespace std;

namespace p15_08 {

    void split_palindrom(const vector<int> & input, vector<list<int>> & set) {
        size_t len = input.size();

        vector<int> s;
        list<int> p;

        for (size_t i = 0; i < len; i++) {
            int c = input[i];
            size_t s_size = s.size();

            if (s_size > 0 && s[s_size - 1] == c) {
                p.push_front(s.back());
                s.pop_back();
                p.push_back(c);

            } else if (s_size > 1 && s[s_size - 2] == c) {
                p.push_front(s.back());
                s.pop_back();
                p.push_front(s.back());
                s.pop_back();
                p.push_back(c);

            } else {
                if (p.size() > 0) {

                    for (auto e: s) {
                        list<int> p_e;
                        p_e.push_back(e);
                        set.push_back(p_e);
                    }
                    s.clear();

                    set.push_back(p);
                    p.clear();

                } 
                s.push_back(c);
            }
        }

        for (auto e: s) {
            list<int> p_e;
            p_e.push_back(e);
            set.push_back(p_e);
        }
        s.clear();

        if (p.size() > 0) {
            set.push_back(p);
            p.clear();
        }
    }

    void test(const vector<int> & input) {
        vector<list<int>> set;
        split_palindrom(input, set);
        for(auto e: set) {
            dump_list(e, true);
        }
    }
}

void test_p15_08_palindrom() {
    PRINT_FUNC_NAME;
    p15_08::test(vector<int> {0, 2, 0, 4, 4, 3, 5, 1, 8, 8, 1, 2});
}