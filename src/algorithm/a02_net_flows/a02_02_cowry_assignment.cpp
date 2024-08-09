#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;

// Cowry assignment (https://www.acmicpc.net/problem/2188)
//                  (https://blog.naver.com/kks227/220804885235)
//
//  - Assign cows to cowry (Each cows has its own favorite cowry)
//  - Utilizing Ford & Fulkerson algorithm
//  - MCM(Maximum Cardinality Matching)/MBM(Maxium Bipartite Matching)
//  - It tooks 2:30 h

#define N_MAX 256
namespace a02_02 {

    template <typename T, int N>
    class Q {
        public:
            Q() {
                memset(buf, 0, sizeof(buf));
            }
            size_t size() {
                if (front_idx < back_idx) {
                    return front_idx + N - back_idx;
                } else {
                    return front_idx - back_idx;
                }
            }

            size_t capa() {
                return N - 1;
            }

            void push(T v) {
                size_t n_f_idx = (front_idx + 1) % N;
                if (n_f_idx != back_idx) {
                    buf[front_idx] = v;
                    front_idx = n_f_idx; 
                }
            }

            T pop() {
                if (size()) {
                    size_t r_idx = back_idx;
                    back_idx = (back_idx + 1) % N;
                    return buf[r_idx];
                }
                return buf[back_idx];
            }

            void dump() {
                cout << "front_idx: " << front_idx << ", back_idx: " << back_idx << 
                            ", (" << size() << "/" << capa() << ")" << "-";
                cout << "{";
                for (size_t i = 0; i < N; i++) {
                    cout << buf[i] << ", ";
                }
                cout << "}" << endl;
            }

        private:
            size_t front_idx = 0; // to be pushed
            size_t back_idx = 0;   // to be popped
            T buf[N];
    };

    void test_q() {
        Q<int, 3> q;
        q.dump();
        q.pop(); q.dump();
        cout << "push 1, 2, 3, 4" << endl;
        q.push(1); q.dump();
        q.push(2); q.dump();
        q.push(3); q.dump();
        q.push(4); q.dump();
        cout << "pop " << q.pop() << " "; q.dump();
        cout << "pop " << q.pop() << " "; q.dump();
        cout << "pop " << q.pop() << " "; q.dump();
        cout << "pop " << q.pop() << " "; q.dump();
        cout << "push 5, 6" << endl;
        q.push(5); q.dump();
        q.push(6); q.dump();
        cout << "pop " << q.pop() << " "; q.dump();
        cout << "pop " << q.pop() << " "; q.dump();
    }

    void dump_graph(int a[][N_MAX], size_t n, size_t m) {
        for (size_t i = 0; i < n; i++) {
            cout << "{";
            for (size_t j = 0; j < m; j++) {
                cout << a[i][j] << ", ";
            }
            cout << "}" << endl;
        }
    }

    // n: number of cow
    // m: number of cowry
    size_t const_graph(int input[][N_MAX], int capa[][N_MAX], size_t n, size_t m) {
        const size_t from = 0;
        const size_t n_base = 1;
        const size_t m_base = n;
        const size_t to = n + m + 1;

        for (size_t i = 0; i < n; i++) {
            size_t cow = n_base + i; // graph node idx for cow
            capa[from][cow] = 1;
            int num_next = input[i][0];
            for (size_t j = 1; j <= (size_t) num_next; j++) {
                size_t cowry = m_base + input[i][j];
                capa[cow][cowry] = 1;
            }
        }

        for (size_t i = 1; i <= m; i++) {
            size_t cowry = m_base + i;
            capa[cowry][to] = 1;
        }
        return to + 1;
    }

    int min_capa(int capa[][N_MAX], int flow[][N_MAX], int prev[], size_t from, size_t to) {
        size_t c = to;
        int min = 0x7FFFFFFF;
        while(c != from) {
            cout << c << "<-";
            size_t p = prev[c];
            int a = capa[p][c] - flow[p][c];
            if (a < min) {
                min = a;
            }
            c = p;
        }
        cout << c << endl;
        return min;
    }

    int dfs(int capa[][N_MAX], int flow[][N_MAX], int prev[], size_t num_nodes, size_t from, size_t to) {
        for(size_t i = 0; i < num_nodes; i++) {
            prev[i] = -1;
        }
        Q<size_t, N_MAX> q;
        q.push(from);

        for (size_t i = 0; q.size() && prev[to] == -1; i++) {
            size_t c = q.pop();
            cout << "pop: " << c << endl;

            for (size_t j = 0; j < num_nodes; j++) {
                if (j == c) {
                    continue;
                }
                if ((capa[c][j] - flow[c][j]) <= 0) {
                    continue;
                }

                if (prev[j] != -1) {
                    continue;
                }

                cout << j << "<-" << c << endl;

                prev[j] = c;
                if (j == to) {
                    return min_capa(capa, flow, prev, from, to);
                }
                q.push(j);
            }
        }
        return -1;
    }

    int max_flow(int capa[][N_MAX], int flow[][N_MAX], int prev[][N_MAX], int num_nodes) {
        int max = 0;
        for (size_t i = 0; i < 10; i++) {
            int amount = 0;
            if (!i) {
                prev[i][5] = 4;
                prev[i][4] = 1;
                prev[i][1] = 0;
                amount = min_capa(capa, flow, prev[i], 0, num_nodes - 1);
            } else {
                cout << "* capa: " << endl;
                dump_graph(capa, num_nodes, num_nodes);
                cout << "* flow: " << endl;
                dump_graph(flow, num_nodes, num_nodes);

                amount = dfs(capa, flow, prev[i], num_nodes, 0, num_nodes - 1);
            }
            cout << "found amount: " << amount << endl;
            if (amount == -1) {
                break;
            }

            size_t c = num_nodes - 1;
            while(c != 0) {
                size_t p = prev[i][c];
                flow[p][c] += amount;
                flow[c][p] -= amount;
                c = p;
            }
            max += amount;
        }
        return max;
    }

    int capa_g[N_MAX][N_MAX];
    int flow_g[N_MAX][N_MAX];
    int prev_g[N_MAX][N_MAX];

    void test(int input[][N_MAX], size_t n, size_t m) {
        memset(capa_g, 0, sizeof(capa_g));
        size_t num_nodes = const_graph(input, capa_g, n, m);
        //dump_graph(capa_g, num_nodes, num_nodes);
        int max = max_flow(capa_g, flow_g, prev_g, num_nodes);
        cout << "max: " << max << endl;
    }
}

void test_a02_02_cowry_assignment() {
    PRINT_FUNC_NAME;
    int i[][N_MAX] = {
        {2, 2, 5},
        {3, 2, 3, 4},
        {2, 1, 5},
        {3, 1, 2, 5,},
        {1, 2}
    };
    //a02_02::test_q();
    //a02_02::test(i, 5, 5);

    int i_2[][N_MAX] = {
        {2, 1, 2},
        {1, 2},
    };
    //a02_02::test_q();
    a02_02::test(i_2, 2, 2);

}