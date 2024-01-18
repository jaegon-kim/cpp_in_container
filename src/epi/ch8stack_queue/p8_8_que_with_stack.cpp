#include <iostream>
#include <optional>
//#include <list>
#include <deque>
#include "utility/dump.hpp"

using namespace std;

namespace p8_8 {

    template <typename T>
    class q_with_stack {
        public:

            q_with_stack() : enq_l(0), deq_l(0) {}

            void push(T v) {
                enq_l.push_front(v);
            }

            optional<T> pop() {
                if (deq_l.empty()) {

                    size_t len = enq_l.size();
                    for (size_t i = 0; i < len; i++) {
                        deq_l.push_front(enq_l.front());
                        enq_l.pop_front();
                    }
                }
                if (deq_l.empty()) {
                    return nullopt;
                }

                T v = deq_l.front();
                deq_l.pop_front();
                return v;
            }

            void dump(bool nl) {
                size_t len = enq_l.size();
                cout << "{";
                for (int i = 0; i < (int) len; i++) {
                    cout << enq_l[i] << ", ";
                }
                len = deq_l.size();
                cout << "_" ;
                for (int i = len - 1; i >= 0; i--) {
                    cout << deq_l[i] << ", ";
                }
                cout << "}";
                if (nl) {
                    cout << endl;
                }                
            }

         private:
            deque<T> enq_l;
            deque<T> deq_l;
    };

    void test() {
        q_with_stack<int> q;

        q.dump(true);

        for(int i = 0; i < 10; i++) {
            q.push(i);
            q.dump(true);
        }

        for(int i = 0; i < 5; i++) {
            auto v = q.pop();
            q.dump(false);
            cout << " POP: " << v.value_or(-1) << endl;  
        }

        for(int i = 0; i < 5; i++) {
            q.push(i);
            q.dump(true);
        }

        for(int i = 0; i < 9; i++) {
            auto v = q.pop();
            q.dump(false);
            cout << " POP: " << v.value_or(-1) << endl;
        }


    }
}

void test_p8_8_que_with_stack() {
    PRINT_FUNC_NAME;
    p8_8::test();
}
