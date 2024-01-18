#include <iostream>
#include <optional>
#include <list>
#include "utility/dump.hpp"

using namespace std;

namespace p8_9 {

    template <typename T>
    class queue {
        public:
            void push(T v) {
                l.push_front(v);

                if (!max_l.empty() && (max_l.back() < v)) {
                    max_l.clear();
                    max_l.push_front(v);
                    return;
                }

                while(!max_l.empty() && (max_l.front() < v)) {
                    max_l.pop_front();
                }
                max_l.push_front(v);
            }

            optional<T> pop() {
                if (l.empty()) {
                    return nullopt;
                }
                T v = l.back();
                l.pop_back();

                if (!max_l.empty() && (max_l.back() == v)) {
                    max_l.pop_back();
                }
                return v;
            }

            optional<T> max() {
                if (max_l.empty()) {
                    return nullopt;
                }
                return max_l.back();
            }

            size_t size() {
                return l.size();
            }

        private:
            list<T> l;
            list<T> max_l;
    };

    void test() {

        queue<int> q;

        vector<int> v {3, 4, 5, 8, 1, 2, 5, 0, 1, 3};
        for (int & a: v) {           
            q.push(a);
            cout << "push " << a << ", max: " << q.max().value_or(-1) << endl;
        }
        while(q.size()) {
            auto v = q.pop();
            cout << "pop " << v.value_or(-1) << ", max: " << q.max().value_or(-1) << endl;
        }
    }
}

void test_p8_9_que_with_max() {
    PRINT_FUNC_NAME;
    p8_9::test();
}