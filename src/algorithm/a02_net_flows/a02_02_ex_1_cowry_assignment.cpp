#include <iostream>
#include <cstring>
#include <utility/dump.hpp>

using namespace std;

#define N_MAX 200
#define M_MAX 200
#define V_MAX (N_MAX + M_MAX + 2)
#define Q_BUF_SZ (V_MAX + 1)
#define PATH_MAX 200

namespace a02_02_ex_1 {

    int capa_g[V_MAX][V_MAX];
    int flow_g[V_MAX][V_MAX];
    int back_log_g[PATH_MAX][V_MAX];

    int cow2v(int c) {
        return c;
    }

    int v2cow(int v) {
        return v;
    }

    int cowry2v(int c, int n) {
        return c + n;
    }

    int v2cowry(int v, int n) {
        return v - n;
    }

    int sink(int n, int m) {
        return n + m + 1;
    }

    int v_size(int n, int m) {
        return sink(n, m) + 1;
    }

    void dump_graph(int v[][V_MAX], int n) {

        cout << "   ";
        for (int j = 0; j < n; j++) {
            cout << j << ", ";
        }
        cout << endl;

        cout << "   ";
        for (int j = 0; j < n; j++) {
            cout << "---";
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << i << "| ";
            for (int j = 0; j < n; j++) {
                cout << v[i][j] << ", ";
            }
            cout << endl;
        }
    }

    class Q {
        public:
            bool empty() {
                return head == tail;
            }

            bool full() {
                return (tail + 1) % Q_BUF_SZ == head;
            }

            bool push(int v) {
                if (full()) {
                    return false;
                }

                buf[tail] = v;
                tail = (tail + 1) % Q_BUF_SZ;
                return true;
            }

            int pop() {
                if (empty()) {
                    return buf[head];
                }
                int r = buf[head];
                head = (head + 1) % Q_BUF_SZ;
                return r;
            }

            int size() {
                if (head <= tail) {
                    return tail - head;
                } else {
                    return (tail + Q_BUF_SZ - head);
                }
            }

            void dump() {
                cout << "(h: " << head << ", t: " << tail << ", s: " << size() << ") ";
                int len = size();
                for (int i = 0; i < len; i++) {
                    cout << buf[(head + i) % Q_BUF_SZ] << ", ";
                }
                cout << endl;
            }

        private:
            int buf[Q_BUF_SZ];
            int head = 0;
            int tail = 0;
    };

    void test_q() {
        Q q;
        q.dump();
        for (int i = 0; i < Q_BUF_SZ + 1; i++ ) {
            q.push(i);
            q.dump();            
        }
        for (int i = 0; i < Q_BUF_SZ + 1; i++ ) {
            cout << "pop: " << q.pop() << endl;
            q.dump();
        } 
        for (int i = 0; i < Q_BUF_SZ + 1; i++ ) {
            q.push(i);
            q.dump();            
        }
    }

    void const_graph(int cow[][M_MAX], int capa[][V_MAX], int flow[][V_MAX], int n, int m) {

        for (int i = 0; i < n; i++) {
            capa[0][i + 1] = 1;
            for (int j = 0; j < cow[i][0]; j++) {
                capa[cow2v(i + 1)][cowry2v(cow[i][j + 1], n)] = 1;
            }            
        }

        for (int i = 0; i < m; i++) {
            capa[cowry2v(i + 1, n)][sink(n, m)] = 1;
        }
    }

    bool bfs(int back_log[V_MAX], int capa[][V_MAX], int flow[][V_MAX], int n, int m, int start, int sink) {

        for (int i = 0; i < v_size(n, m); i++) {
            back_log[i] = -1;
        }

        Q q;
        q.push(start);

        while(!q.empty()) {
            int c = q.pop();
            if (c == sink) {
                cout << "found" << endl;
                return true; 
            }
            for (int i = 0; i < v_size(n, m); i++) {
                if (i == c || back_log[i] != -1) {
                    continue;
                }
                if ((capa[c][i] - flow[c][i]) > 0) {
                    back_log[i] = c;
                    q.push(i);
                }
            }
        }
        cout << "not found" << endl;
        return false;
    }    

    int min_capa(int back_log[V_MAX], int start, int sink, int capa[][V_MAX], int flow[][V_MAX]) {
        int c = sink;
        int min = 0x7FFFFFFF;
        while(c != start) {
            cout << c << "<-";
            int p = back_log[c];

            int avail_capa = capa[p][c] - flow[p][c];
            if (avail_capa < min) {
                min = avail_capa;
            }
            c = p;
        }
        cout << c << endl;
        return min;
    }

    void update_flow(int back_log[V_MAX], int start, int sink, int flow[][V_MAX], int min) {
        int c = sink;
        while(c != start) {
            int p = back_log[c];
            flow[p][c] += min;
            flow[c][p] -= min;
            c = p;
        }
    }

    void test(int cow[][M_MAX], int n, int m) {
        memset(capa_g, 0, sizeof(capa_g));
        memset(flow_g, 0, sizeof(flow_g));
        const_graph(cow, capa_g, flow_g, n, m);
        dump_graph(capa_g, v_size(n, m));

        int total_capa = 0;
        for (int i = 0; i < 100; i++) {
            bool found = bfs(back_log_g[i], capa_g, flow_g, n, m, 0, sink(n, m));
            if (!found) {
                break;
            }
            int min = min_capa(back_log_g[i], 0, sink(n, m), capa_g, flow_g);
            total_capa += min;
            //cout << min << endl;
            update_flow(back_log_g[i], 0, sink(n, m), flow_g, min);
        }

        cout << "max capa: " << total_capa << endl;
    }

}

void test_a02_02_ex_1_cowry_assignment() {
    PRINT_FUNC_NAME;
    int cow[][M_MAX] = {
        {2, 2, 5},
        {3, 2, 3, 4},
        {2, 1, 5},
        {3, 1, 2, 5,},
        {1, 2}
    };
    a02_02_ex_1::test(cow, 5, 5);
    //a02_02_ex_1::test_q();
}