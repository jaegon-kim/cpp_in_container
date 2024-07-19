#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;
#define MAX_NUM_V 1024

namespace a02_01 {

    template <typename T>
    void dump_array(T a[][MAX_NUM_V], size_t len) {
        for (size_t i = 0; i < len; i++) {
            cout << "{";
            for (size_t j = 0; j < len; j++) {
                cout << a[i][j] << ",";
            }
            cout << "}" << endl;
        }
    }

    template <typename T, size_t buf_size>
    class Q {
        public:
            Q() {
                memset(buf, 0, sizeof(buf));
            }

            size_t capa() {
                return buf_size - 1;
            }
            
            size_t size() {
                if (b_idx > f_idx) {
                    return f_idx + buf_size - b_idx;
                } else {
                    return f_idx - b_idx;
                }
            }

            bool is_full() {
                return size() == capa();
            }

            void push_front(T v) {
                if (size() == capa()) {
                    return;
                }
                buf[f_idx] = v;
                f_idx = (f_idx + 1) % buf_size;
            }

            T pop_back() {
                if (f_idx == b_idx) { // empty
                    return buf[b_idx];
                }
                size_t ret_idx = b_idx;
                b_idx = (b_idx + 1) % buf_size;
                return buf[ret_idx];
            }

            void dump(bool nl) {
                cout << "f_idx: " << f_idx << ", b_idx: " << b_idx << "(" << size() << "/" << capa() << ")" << endl;
                cout << "{";
                for (size_t i = 0; i < buf_size; i++) {
                    cout << buf[i] << ", ";
                } 
                cout << "}";
                if (nl) {
                    cout << endl;
                }
            }

        private:
            size_t f_idx = 0;
            size_t b_idx = 0;
            T buf[buf_size];
    };

    void test_q() {
        Q<size_t, 3> q;
        q.dump(true);
        q.push_front(1); q.dump(true);
        cout << "popped: " << q.pop_back() << endl; q.dump(true);
        q.push_front(1); q.dump(true);
        q.push_front(2); q.dump(true);
        q.push_front(3); q.dump(true);
        cout << "is ful ? " << q.is_full() << endl;
        cout << "popped: " << q.pop_back() << endl; q.dump(true);
        cout << "popped: " << q.pop_back() << endl; q.dump(true);
        q.push_front(1); q.dump(true);
        cout << "popped: " << q.pop_back() << endl; q.dump(true);
    }

    void construct_graph(tuple<int, int, int> e[], size_t num_e, int capa[][MAX_NUM_V]) {
        for (size_t i = 0; i < num_e; i++) {
            capa[get<0>(e[i])][get<1>(e[i])] = get<2>(e[i]);
        }
    }

    int capa[MAX_NUM_V][MAX_NUM_V], flow[MAX_NUM_V][MAX_NUM_V];


    int dfs(int capa[][MAX_NUM_V], int flow[][MAX_NUM_V], int prev[], int from, int to, int num_v) {

        for (int i = 0; i < num_v; i++) {
            prev[i] = -1;
        }

        Q<int, MAX_NUM_V> q;
        q.push_front(from);
        prev[from] = from;

        while(q.size() && prev[to] == -1) {
            int c = q.pop_back();
            //cout << "pop: " << c << endl;
            for (int i = 0; i < num_v; i++) {
                if (prev[i] != -1) {
                    continue;
                }
                int r = capa[c][i] - flow[c][i];
                if (r > 0) {
                    if (i == from) {
                        break;
                    }
                    prev[i] = c;
                    q.push_front(i);
                }
            }
        }

        if (prev[to] == -1) {
            return 0;
        }

        int c = to; // current
        int min_r = 0x7FFFFFFFU;
        while(c != from) {
            int p = prev[c];
            int r = capa[p][c] - flow[p][c];
            if (r < min_r) {
                min_r = r;
            }
            c = p;
        }
        return min_r;
    }

    int prev_arr[MAX_NUM_V][MAX_NUM_V];

    void update_flow(int prev[], int flow[][MAX_NUM_V], int from, int to, int alloc, bool print_path) {
        int c = to;
        while (c != from) {
            if (print_path) {
                cout << c << "<-";
            }
            int p = prev[c];
            flow[p][c] += alloc;
            flow[c][p] -= alloc;
            c = p;
        }
        if (print_path) {
            cout << c << "(alloc: " << alloc << ")" << endl;
        }
    }

    int ford_fulkerson(int capa[][MAX_NUM_V], int flow[][MAX_NUM_V], int from, int to, int num_v) {
        ///*
        // pre allocation for testing
        prev_arr[0][3] = 2;
        prev_arr[0][2] = 1;
        prev_arr[0][1] = 0;
        prev_arr[0][0] = 0;
        update_flow(prev_arr[0], flow, from, to, 1, true);

        prev_arr[1][3] = 2;
        prev_arr[1][2] = 0;
        prev_arr[1][0] = 0;
        update_flow(prev_arr[1], flow, from, to, 1, true);

        for (size_t i = 2; i < MAX_NUM_V; i++) {
        //*/

        //for (size_t i = 0; i < MAX_NUM_V; i++) {
            // cout << "capa:" << endl;
            // dump_array(capa, num_v);
            // cout << "flow:" << endl;
            // dump_array(flow, num_v);

            int alloc = dfs(capa, flow, prev_arr[i], from, to, num_v);

            if (alloc) {
                update_flow(prev_arr[i], flow, from, to, alloc, true);
            } else {
                break; // no more available paths
            }
        }

        return 0;
    }

    void test(tuple<int, int, int> e[], size_t from, size_t to, size_t num_e, size_t num_v) {
        // The size of capa/flow: 4194304 (1024 * 1024 * 4)
        // Not to locate big size memory on the stack (use global or heap)
        // int capa[MAX_NUM_V][MAX_NUM_V], flow[MAX_NUM_V][MAX_NUM_V];
        memset(capa, 0, sizeof(capa));
        memset(flow, 0, sizeof(flow));
        construct_graph(e, num_e, capa);

        ford_fulkerson(capa, flow, from, to, num_v);
    }
}

void test_a02_01_ford_fulkerson() {
    PRINT_FUNC_NAME;
    //a02_01::test_q();
    tuple<int, int, int> e[] = {
        {0, 1, 1}, {0, 2, 3}, {1, 2, 1}, {1, 3, 1}, {2, 3, 2}
    };
    a02_01::test(e, 0, 3, 5, 4);
}