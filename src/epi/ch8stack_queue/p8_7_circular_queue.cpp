#include <iostream>
#include <memory>
#include <vector>
#include <optional>

#include "utility/dump.hpp"

using namespace std;

namespace p8_7 {

    template <typename T>
    class circular_queue {
        public:
            bool enque(T t) {
                if (tail == next_idx(head)) {
                    return false;
                }
                v[head] = t;
                head = next_idx(head);
                return true;     
            }

            optional<T> deque() {
                if (tail == head) {
                    return nullopt;
                }
                T tmp = v[tail];
                tail = next_idx(tail);
                return tmp;
            }

            size_t size() {
                if (head >= tail) {
                    return head - tail;
                } else {
                    return q_end - tail + head - 1;
                }
            }

            void inc_qsize(size_t s) {
                size_t new_q_end = s - 1;
                if (new_q_end < q_end) {
                    return; // not supporting
                }

                if (head < tail) {
                    size_t diff = new_q_end - q_end;
                    for (int i = q_end; i >= (int)tail; i--) {
                        v[i + diff] = v[i];
                    }
                }
                q_end = new_q_end;
                return;
            }

            void dump(bool nl) {
                cout << "size: " << size();
                cout << "{";
                if (head >= tail) {
                    for(int i = head - 1; i >= (int)tail; i--) {
                        cout << v[i] << ", ";
                    }
                } else {
                    for(int i = head - 1; i >= 0; i--) {
                        cout << v[i] << ", ";
                    }
                    for(int i = q_end; i >= (int)tail; i--) {
                        cout << v[i] << ", ";
                    }
                }
                cout << "}";
                if (nl) {
                    cout << endl;
                }
            }

        private:
            size_t next_idx(const size_t idx) {
                return ((idx + 1) > q_end ? 0 : idx + 1);
            }

            size_t prev_idx(const size_t idx) {
                return (idx == 0? q_end: idx - 1);
            }

            T v[512];
            size_t len;
            size_t head = 0; // place to be added
            size_t tail = 0; // place to be return
            size_t q_end = 0;
    };

    void test() {
        circular_queue<int> q;
        q.inc_qsize(10);

        for(int i = 0; i < 10; i++) {
            q.enque(i);
            q.dump(true);
        }

        for(int i = 0; i < 5; i++) {
            q.deque();
            q.dump(true);
        }

        for(int i = 0; i < 5; i++) {
            q.enque(i);
            q.dump(true);
        }

        for(int i = 0; i < 5; i++) {
            q.deque();
            q.dump(true);
        }

        q.inc_qsize(20);

        for(int i = 0; i < 10; i++) {
            q.enque(i);
            q.dump(true);
        }

        for(int i = 0; i < 10; i++) {
            q.deque();
            q.dump(true);
        }

    }
}

void test_p8_7_circular_queue() {
    PRINT_FUNC_NAME;
    p8_7::test();
}