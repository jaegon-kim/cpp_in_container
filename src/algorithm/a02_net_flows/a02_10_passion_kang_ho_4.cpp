
// https://www.acmicpc.net/problem/11378
// Passsion Kangho #4 (열혈강호 4)
// N: number of employ, M: number of task (1<= N, M <=1000)
// K: Penalty (Which can be distributed to employs)

#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;

#define MAX_N 1000
#define MAX_M 1000
#define MAX_NODE (MAX_N + MAX_M + 2)

namespace a02_10 {

    template <typename T, int N>
    class Q {
        public:

            void push_front(T v) {
                if (size() == capa()) {
                    cout << "Q is full" << endl;
                    return;
                }
                buf[front_idx] = v;
                front_idx = (front_idx + 1) % N;
            }

            T pop_back() {
                if (!size()) {
                    cout << "Q is empty" << endl;
                    return buf[back_idx];
                }
                size_t r_idx = back_idx;
                back_idx = (back_idx + 1) % N;
                return buf[r_idx];
            }

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

            void dump() {
                cout << "front: " << front_idx << ", back: " << back_idx << "(" << size() << "/" << capa() << ")" << endl;
                cout << "{";
                for (const auto & e: buf) {
                    cout << e << ", ";
                }
                cout << "}" << endl;                
            }


        private:
            T buf[N];
            size_t front_idx = 0;
            size_t back_idx = 0;
    };

    void test_q() {
        Q<int, 3> q;
        q.dump();
        q.push_front(1); q.dump();
        q.push_front(2); q.dump();
        q.push_front(3); q.dump();
        cout << "pop: " << q.pop_back() << endl;
        cout << "pop: " << q.pop_back() << endl;
        cout << "pop: " << q.pop_back() << endl;
        q.dump();
        q.push_front(4); q.dump();
        q.push_front(5); q.dump();
        q.push_front(6); q.dump();
        cout << "pop: " << q.pop_back() << endl;
        cout << "pop: " << q.pop_back() << endl;
        cout << "pop: " << q.pop_back() << endl;
        q.dump();

    }

    static inline int s_node() {
        return 0;
    }

    static inline int k_node() {
        return 1;
    }

    static inline int n2node(int n) {
        return k_node() + n;
    }

    static inline int last_n_node(int size_n) {
        return k_node() + size_n;
    }

    static inline int m2node(int m, int size_n) {
        return last_n_node(size_n) + m;
    }

    static inline int last_m_node(int size_n, int size_m) {
        return last_n_node(size_n) + size_m;
    }

    static inline int t_node(int size_n, int size_m) {
        return last_m_node(size_n, size_m) + 1;
    }

    static inline int size_node(int size_n, int size_m) {
        return size_n + size_m + 3; // s, k, t, n..., m...
    }

    void const_graph(const int input[][MAX_M], int capa[][MAX_NODE], int size_n, int size_k, int s, int t) {

        capa[s][k_node()] = size_k;

        for (int i = 0; i < size_n; i++) {
            int n = i + 1;
            int n_node = n2node(n);
            capa[s][n_node] = 1;
            //capa[k_node()][n_node] = 1;
            capa[k_node()][n_node] = size_k;

            for (int j = 1; j <= input[i][0]; j++) {
                int m_node = m2node(input[i][j], size_n);
                capa[n_node][m_node] = 1;
                capa[m_node][t] = 1;
            }
        }

    }

    void dump_graph(int g[][MAX_NODE], int size_node) {

        cout << "   ";
        for (int j = 0; j < size_node; j++) {
            //cout << g[i][j] << ", ";
            printf("%2d,", j);
        }
        cout << endl;


        for (int i = 0; i < size_node; i++) {
            printf("%2d ", i);
            cout << "{";
            for (int j = 0; j < size_node; j++) {
                cout << g[i][j] << ", ";
            }
            cout << "}" << endl;
        }
        cout << endl;
    }

    void dump_assignment(int g[][MAX_NODE], int size_n, int size_m) {
        for (int n = 1; n <= size_n; n++) {
            int node_n = n2node(n);
            for (int m = 1; m <= size_m; m++) {
                int node_m = m2node(m, size_n);
                if (g[node_n][node_m]) {
                    cout << n << "->" << m << endl;
                }
            }
        }
    }

    int min_amount(int capa[][MAX_NODE], int flow[][MAX_NODE], int prev[], int s, int t) {
        int c = t;
        int min_amount = 0x7FFFFFFF;
        while(c != s) {
            cout << c << "<-";
            int p = prev[c];
            int amount = capa[p][c] - flow[p][c];
            if (min_amount > amount) {
                min_amount = amount;
            }
            c = p;
        }
        cout << c << endl;
        return min_amount;
    }

    int bfs(int capa[][MAX_NODE], int flow[][MAX_NODE], int prev[], int size_node, int s, int t) {
        for (int i = 0; i < size_node; i++) {
            prev[i] = -1;
        }

        Q<int, MAX_NODE + 1> q;
        q.push_front(s);

        while(q.size() && prev[t] == -1) {
            int c = q.pop_back();
            for (int i = 0; i < size_node; i++) {
                if (c == i) {
                    continue;
                }

                if (prev[i] != -1) {
                    continue;
                }

                int avail = capa[c][i] - flow[c][i];
                if (avail <= 0) {
                    continue;
                }

                prev[i] = c;

                if (i == t) {
                    return min_amount(capa, flow, prev, s, t);
                }
                q.push_front(i);
            }
        }
        return 0;
    }

    int max_job(int capa[][MAX_NODE], int flow[][MAX_NODE], int prev[][MAX_NODE], int final[][MAX_NODE], 
                    int size_n, int size_m, int s, int t) {

        int job_cnt = 0;
        for(size_t i = 0; true ; i++) {
            int amount = bfs(capa, flow, prev[i], size_node(size_n, size_m), s, t);
            if (!amount) {
                break;
            }
            job_cnt += amount;

            int c = t;
            while(c != s) {
                int p = prev[i][c];
                flow[p][c] += amount;
                flow[c][p] -= amount;
                if (capa[p][c] > 0) {
                    final[p][c] += amount;
                } else {
                    final[c][p] -= amount;
                }
                c = p;
            }
        }
        return job_cnt;
    }

    int capa_g[MAX_NODE][MAX_NODE];
    int flow_g[MAX_NODE][MAX_NODE];
    int prev_g[MAX_NODE][MAX_NODE];
    int final_g[MAX_NODE][MAX_NODE];

    void test(const int input[][MAX_M], int size_n, int size_k, int size_m) {
        memset(capa_g, 0, sizeof(capa_g));
        memset(flow_g, 0, sizeof(capa_g));
        memset(final_g, 0, sizeof(capa_g));

        const_graph(input, capa_g, size_n, size_k, s_node(), t_node(size_n, size_m));
        //dump_graph(capa_g, size_node(size_n, size_m));
        int r = max_job(capa_g, flow_g, prev_g, final_g, size_n, size_m, s_node(), t_node(size_n, size_m));
        cout << "r: " << r << endl;
        // dump_graph(final_g, size_node(size_n, size_m));
        // dump_assignment(final_g, size_n, size_m);
    }
}

void test_a02_10_passion_kang_ho_4() {
    PRINT_FUNC_NAME;

    const int input_1[][MAX_M] = {
        {5, 1, 2, 3, 4, 5}, 
        {1, 1}, 
        {1, 1}, 
        {1, 1}, 
        {2, 1, 5}, 
    };

    for (int i = 1; i <= 5; i++) {
        a02_10::test(input_1, 5, i, 5);
    }
}