#include <iostream>
#include <cstring>
#include <utility/dump.hpp>

using namespace std;

#define N_MAX 200
#define M_MAX 200
#define V_MAX (N_MAX + M_MAX + 2)
#define PATH_MAX 200

namespace a02_02_ex_1 {

    template <int BUF_SIZE>
    class Q {
        public:
            size_t size() {
                if (head > tail) {
                    return tail + BUF_SIZE - head;
                } else {
                    return tail - head;
                }
            }

            void push(int v) {
                if (size() == (BUF_SIZE - 1)) {
                    return;
                }
                buf[tail] = v;
                tail = (tail + 1) % BUF_SIZE;
            }

            int pop() {
                if (!size()) {
                    return buf[head];
                }
                int r = buf[head];
                head = (head + 1) % BUF_SIZE;
                return r;
            }

            void dump() {
                cout << "(h:" << head << ", t: " << tail << ", size: " << size() << ") {";
                int len = size();
                for (int i = 0; i < len; i++) {
                    cout << buf[(head + i) % BUF_SIZE] << ", ";
                }
                cout << "}" << endl;
            }

        private:
            int head = 0;
            int tail = 0;
            int buf[BUF_SIZE];
    };

    void test_q() {
        Q<3> q;
        q.dump();
        for (int i = 0; i < 4; i++) {
            q.push(i);
            q.dump();
        }

        for (int i = 0; i < 1; i++) {
            cout << "pop: " << q.pop() << " ";
            q.dump();
        }

        for (int i = 0; i < 1; i++) {
            q.push(i);
            q.dump();
        }

        for (int i = 0; i < 3; i++) {
            cout << "pop: " << q.pop() << " ";
            q.dump();
        }

    }

    void const_graph(int cow[][M_MAX], int capa[][V_MAX], int n, int m) {
        for (int i = 0; i < n; i++) {
            capa[0][i + 1] = 1;

            int sz = cow[i][0];
            for (int j = 0; j < sz; j++) {
                capa[i + 1][n + cow[i][j + 1]] = 1;
            }
        }

        for (int i = 0; i < m; i++) {
            capa[n + i + 1][n + m + 1] = 1;
        }
    }

    void dump_graph(int g[][V_MAX], int sz) {
        cout << "   ";
        for (int i = 0; i < sz; i++) {
            cout << i << ", ";
        }
        cout << endl;
        cout << "   ";
        for (int i = 0; i < sz; i++) {
            cout << "---";
        }
        cout << endl;
        for (int i = 0; i < sz; i++) {
            cout << i << "| ";
            for (int j = 0; j < sz; j++) {
                cout << g[i][j] <<  ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    int min_capa(int capa[][V_MAX], int flow[][V_MAX], int path[], int sz) {
        int c = sz - 1;
        int min = 0X7FFFFFFF;
        while (c != 0) {
            int prev = path[c];
            int a = capa[prev][c] - flow[prev][c];
            if (a < min) {
                min = a;
            }
            c = prev;
        }
        return min;
    }

    void update_flow(int flow[][V_MAX], int path[], int sz, int min_c) {
        int c = sz - 1;
        while (c != 0) {
            int prev = path[c];
            flow[prev][c] += min_c;
            flow[c][prev] -= min_c;
            c = prev;
        }
    }


    bool dfs(int capa[][V_MAX], int flow[][V_MAX], int path[], int sz) {

        for (int i = 0; i < sz; i++) {
            path[i] = -1;
        }
        Q<V_MAX> q;
        q.push(0);

        while(q.size()) {
            int c = q.pop();
            if (c == (sz - 1)) {
                return true;
            }

            for (int i = 0; i < sz; i++) {
                if ((i == c) || (path[i] != -1)) {
                    continue;
                }

                if ((capa[c][i] - flow[c][i]) > 0 ) {
                    q.push(i);
                    path[i] = c;
                }
            }
        }
        return false;
    }
    
    int capa_g[V_MAX][V_MAX];
    int flow_g[V_MAX][V_MAX];
    int path_g[V_MAX][V_MAX];

    int max_assign(int capa[][V_MAX], int flow[][V_MAX], int path[][V_MAX], int sz) {
        int total_c = 0;
        for (int i = 0; i < sz; i++) {
            if (!dfs(capa, flow, path[i], sz)) {
                return total_c;
            }
            int min_c = min_capa(capa, flow, path[i], sz);
            update_flow(flow, path[i], sz, min_c);
            total_c += min_c;
        }
        return -1;        
    }

    void test(int cow[][M_MAX], int n, int m) {
        memset(capa_g, 0, sizeof(capa_g));
        memset(flow_g, 0, sizeof(flow_g));

        const_graph(cow, capa_g, n, m);
        //dump_graph(capa_g, n + m + 2);
        int r = max_assign(capa_g, flow_g, path_g, n + m + 2);
        cout << "max assign: " << r << endl;
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