#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;

// Finding the max number of path between 2 cities, but the city in the path also should be exclusive
//    https://www.acmicpc.net/problem/2316
//    https://blog.naver.com/kks227/220804885235

#define MAX_N 1024
namespace a02_04 {

    template <typename T, int N>
    class Q {
        public:
            size_t capa() {
                return N - 1;
            }

            size_t size() {
                if (front_idx < back_idx) {
                    return front_idx + N - back_idx;
                } else {
                    return front_idx - back_idx;
                }
            }

            void push(T v) {
                if (size() == capa()) {
                    cout << "Q is full" << endl;
                    return;
                }
                buf[front_idx] = v;
                front_idx = (front_idx + 1) % N; 
            }

            T pop() {
                if (!size()) {
                    cout << "Q is empty" << endl;
                    return buf[back_idx];
                }
                size_t r_idx = back_idx;
                back_idx = (back_idx + 1) % N;
                return buf[r_idx];
            }

            void dump() {
                cout << "front_idx: " << front_idx << ", back_idx: " << back_idx << "(" << size() << "/" << capa() << ") {";
                for (size_t i = 0; i < N; i++) {
                    cout << buf[i] << ", ";
                }
                cout << "}" << endl;
            }

        private:
            size_t front_idx = 0; // loc to push
            size_t back_idx  = 0; // loc to pop
            T  buf[N];
    };


    void test_q() {
        Q<int, 3> q;
        q.dump();
        cout << "push 1, 2, 3" << endl;
        q.push(1); q.dump();
        q.push(2); q.dump();
        q.push(3); q.dump();
        cout << "pop " << q.pop() << endl;
        cout << "pop " << q.pop() << endl;
        cout << "pop " << q.pop() << endl;

        cout << "push 4, 5, 6" << endl;
        q.push(4); q.dump();
        q.push(5); q.dump();
        q.push(6); q.dump();
        cout << "pop " << q.pop() << endl;
        cout << "pop " << q.pop() << endl;
        cout << "pop " << q.pop() << endl;

        q.push(7); q.dump();
        cout << "pop " << q.pop() << endl;
        q.push(8); q.dump();
        cout << "pop " << q.pop() << endl;


    }

    void dump(const int arr[][MAX_N], size_t n) {
        for (size_t i = 1; i <= n; i++) {
            cout << "{";
            for (size_t j = 1; j <= n; j++) {
                cout << arr[i][j] << ", ";
            }
            cout << "}" << endl;
        }
    }

    int capa_g[MAX_N][MAX_N];
    int flow_g[MAX_N][MAX_N];
    int prev_g[MAX_N][MAX_N];

    int e_i(int e, __attribute__((unused)) int n) {
        return e;
    }

    int e_o(int e, int n) {
        return e + n;
    }

    int io2e(int i_o, int n) {
        if (i_o > n) {
            return i_o - n;
        } else {
            return i_o;
        }
    }

    void construct_graph(const int input[][MAX_N], int n, int p, int capa[][MAX_N]) {
        for (int i = 1; i <= n; i++) {
            capa[e_i(i, n)][e_o(i, n)] = 1;
        }
        for (int i = 0; i < p; i++) {
            capa[e_o(input[i][0], n)][e_i(input[i][1], n)] = 1;
        }
    }

    int dfs(int capa[][MAX_N], int flow[][MAX_N], int prev[], int n, int from, int to) {
        for (int i = 1; i <= n; i++) {
            prev[i] = -1;           
        }
        Q<int, MAX_N> q;
        q.push(from);

        int min_amount = 0x7FFFFFFF;
        while(q.size() && prev[to] == -1) {
            int c = q.pop();
            for (int i = 1; i <= n; i++) {
                if (prev[i] != -1) {
                    continue;
                }

                if (c == i) {
                    continue;
                }

                int amount = capa[c][i] - flow[c][i];
                if (amount <= 0) {
                    continue;
                }

                prev[i] = c;
                q.push(i);
                if (amount < min_amount) {
                    min_amount = amount;
                }

                if (i == to) {
                    return min_amount;
                }
            }
        }
        return 0;
    }

    int max_path(int capa[][MAX_N], int flow[][MAX_N], int prev[][MAX_N], int n, int from, int to) {
        int max = 0;
        for (size_t i = 0; i < 10; i++) {
            int amount = dfs(capa, flow, prev[i], n, from, to);
            if (!amount) {
                break;
            }
            max++;
            int c = to;
            while(c!=from) {
                cout << c << "(" << io2e(c, n/2) << ")" << "<-" ;
                int p = prev[i][c];
                flow[p][c] += amount;
                flow[c][p] -= amount;
                c = p;
            }
            cout << c << "(" << io2e(c, n/2) << ")" << endl;
        }
        return max;
    }

    void test(const int input[][MAX_N], int n, int p) {
        memset(capa_g, 0, sizeof(capa_g));
        memset(flow_g, 0, sizeof(flow_g));
        memset(prev_g, 0, sizeof(prev_g));
        construct_graph(input, n, p, capa_g);
        //dump(capa_g, n * 2);
        int max = max_path(capa_g, flow_g, prev_g, n * 2, e_o(1, n), e_i(2, n));
        cout << "max number of path: " << max << endl;
    }
}

void test_a02_04_city_path_exclusive_city() {
    PRINT_FUNC_NAME;
    //a02_04::test_q();
    const int input_1[][MAX_N] = {
        {1, 3}, {3, 2}, {1, 5}, {5, 4}, {4, 2},
    };
    a02_04::test(input_1, 5, 5);

    const int input_2[][MAX_N] = {
        {1, 3}, {3, 2}, {1, 4}, {4, 2}, {1, 5}, {5, 6}, {6, 2}
    };
    a02_04::test(input_2, 6, 7);

    const int input_3[][MAX_N] = {
        {1, 3}, {1, 4}, {3, 5}, {4, 5}, {5, 6}, {5, 7}, {6, 2}, {7, 2},
    };
    a02_04::test(input_3, 7, 8);

}
