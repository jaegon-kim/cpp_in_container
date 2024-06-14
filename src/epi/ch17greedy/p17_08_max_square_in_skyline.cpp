#include <iostream>
#include <vector>
#include <list>
#include "utility/dump.hpp"
using namespace std;
namespace p17_08 {

    pair<size_t, size_t> max_square(const vector<int> & h_v) {
        list<pair<int, size_t>> stack;

        pair<int, size_t> top;
        pair<size_t, size_t> max_idx;
        int max = 0;

        for (size_t i = 0; i < h_v.size(); i++) {

            pair<int, size_t> cur = make_pair(h_v[i], i);

            while(stack.size() > 0) {
                top = stack.front();
               if (top.first > cur.first) {
                    int square_area = top.first * (i - top.second);
                    if (square_area > max) {
                        max = square_area;
                        max_idx.first = top.second;
                        max_idx.second = i;
                    }
                    cur.second = top.second;
                    stack.pop_front();
                } else {
                    break;
                }
            }

            if (!stack.size()) {
                stack.push_front(cur);
            } else {
                int f_h = stack.front().first;
                if (f_h != h_v[i]) {
                    stack.push_front(cur);
                }                                
            }
            //dump_list_of_pair(stack, true);
        }

        while(stack.size() > 0) {
            top = stack.front();
            int square_area = top.first * (h_v.size() - 1 - top.second);
            //cout << "square_are: " << square_area << endl;
            if (square_area > max) {
                max = square_area;
                max_idx.first = top.second;
                max_idx.second = h_v.size() - 1;
            }
            stack.pop_front();
        }

        return max_idx;
    }

    void test(const vector<int> & h_v) {
        auto r = max_square(h_v);
        cout << r.first << ", " << r.second << endl;
    }
}

void test_p17_08_max_square_in_skyline() {
    PRINT_FUNC_NAME;
    p17_08::test(vector<int> {1, 4, 2, 5, 6, 3, 2, 6, 6, 5, 2, 1, 3, 3});
}   