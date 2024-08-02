#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;

// making grid 0 - https://www.acmicpc.net/problem/11495
//  ref : https://blog.naver.com/kks227/220804885235


#define MAX_ROW 2
#define MAX_COL 50
#define MAX_NODE (MAX_ROW * MAX_COL + 2)
#define INFINITE 9

namespace a02_05 {

    template <typename T, int N>
    class Q {
        public:
            int capa() {
                return N - 1;
            }

            int size() {
                if (idx_back > idx_front) {
                    return idx_front + N - idx_back;
                } else {
                    return idx_front - idx_back;
                }
            }

            void push_front(T v) {
                if (size() == capa()) {
                    cout << "q is full" << endl;
                    return;
                }
                buf[idx_front] = v;
                idx_front = (idx_front + 1) % N;
                return;
            }

            T pop_back() {
                if (!size()) {
                    cout << "q is empty" << endl;
                    return buf[idx_back];
                }
                int r_idx = idx_back;
                idx_back = (idx_back + 1) % N;
                return buf[r_idx];
            }

            void dump() {
                cout << "front: " << idx_front << ", back: " << idx_back << " (" << size() << "/" << capa() << ")" << endl;
                cout << "{";
                for (size_t i = 0; i < N; i++) {
                    cout << buf[i] << ", ";
                }
                cout << "}" << endl;
            }

        private:
            int idx_front = 0; // loc to push
            int idx_back  = 0; // loc to pop
            T buf[N];
    };


    void test_q() {
        Q<int, 3> q;
        q.dump();
        q.pop_back();
        q.push_front(1); q.dump();
        q.push_front(2); q.dump();
        q.push_front(3); q.dump();
        cout << q.pop_back() << endl;
        q.dump();
        q.push_front(4); q.dump();
        cout << q.pop_back() << endl;
        q.dump();
        cout << q.pop_back() << endl;
        q.dump();
        cout << q.pop_back() << endl;
        q.dump();
    }

    static inline int node_base() {
        return 1;
    }

    static inline int loc2node(int c, int r, int m) {
        return m * r + c + node_base();
    }

    static inline pair<int, int> node2loc(int node, int m) {
        int r = node - node_base();
        return make_pair<int, int>(r%m, r/m);
    }

    static inline int endnode(int n, int m) {
        return n * m + node_base();
    }

    void dump(const int arr[][MAX_NODE], int n) {
        for (int i = 0 ; i <= n ; i++) {
            cout << "{";
            for (int j = 0; j <= n; j++) {
                cout << arr[i][j] << ", ";
            }
            cout << "}" << endl;
        }
    }

    void const_graph(const int input [][MAX_COL], int n, int m, int capa[][MAX_NODE]) {
        int t_node = endnode(n, m);
        const int dir[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (((!(r%2)) && (!(c%2))) || ((r%2) && (c%2))) {
                    capa[0][loc2node(c, r, m)] = input[r][c];
                    for (auto & e: dir) {
                        int n_c = c + e[0]; 
                        int n_r = r + e[1];
                        if ((n_c >= 0 && n_c < m) && (n_r >= 0 && n_r < n)) {
                            capa[loc2node(c, r, m)][loc2node(n_c, n_r, m)] = INFINITE;
                        }
                    }
                } else {
                    //cout << c << ", " << r << "=" << input[r][c] << endl;  
                    capa[loc2node(c, r, m)][t_node] = input[r][c];
                }
            }
        } 
    }

    int dfs(int capa[][MAX_NODE], int flow[][MAX_NODE], int prev[], int end_node, int from, int to) {
        for (int i = 0 ; i <= end_node; i++) {
            prev[i] = -1;
        }

        Q<int, MAX_NODE> q;
        q.push_front(from);

        while(q.size() && prev[to] == -1) {
            int c = q.pop_back();
            for (int i = 0; i <= end_node; i++) {
                if (prev[i] != -1) {
                    continue;
                }

                if (!capa[c][i]) {
                    continue;
                }
 
                if (capa[c][i] != INFINITE) {
                    if (( capa[c][i] - flow[c][i]) <= 0) {
                        continue;
                    }
                }

                prev[i] = c;
                q.push_front(i);  

                if (i == to) {
                    int min_amount = 0x7FFFFFFF;

                    int cur = to;
                    while(cur != from) {
                        int p = prev[cur];
                        if (capa[p][cur] != INFINITE) {
                            int amount = capa[p][cur] - flow[p][cur];
                            if (amount < min_amount) {
                                min_amount = amount;
                            }
                        }
                        cur = p;
                    }

                    return min_amount;
                }
            }
        }
        return 0;
    }

    int capa_g[MAX_NODE][MAX_NODE];
    int flow_g[MAX_NODE][MAX_NODE];
    int prev_g[MAX_NODE][MAX_NODE];

    int max_flow(int capa[][MAX_NODE], int flow[][MAX_NODE], int end_node, int from, int to) {

        int num_flows = 0;
        for(int i = 0; i < 10; i++) {
            int amount = dfs(capa, flow, prev_g[i], end_node, from, to);
            if (!amount) {
                break;
            }
            num_flows += amount;
            cout << "amount: " << amount << endl;
            int c = to;
            while(c != from) {
                int p = prev_g[i][c];
                cout << c << "<-";
                if (capa[p][c] != INFINITE) {
                    flow[p][c] += amount;
                    flow[c][p] -= amount;
                }
                c = p;
            }
            cout << c << endl;
            
        }

        return num_flows;
    }

    int cnt_last(int n, int m, int capa[][MAX_NODE], int flow[][MAX_NODE], int end_node) {
        int last = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                int amount = 0;
                if (((!(r%2)) && (!(c%2))) || ((r%2) && (c%2))) {
                    amount = capa[0][loc2node(c, r, m)] - flow[0][loc2node(c, r, m)];
                } else {
                    amount = capa[loc2node(c, r, m)][end_node] - flow[loc2node(c, r, m)][end_node];
                }

                if (amount) {
                    cout << loc2node(c, r, m) << ": " << amount << endl;
                    last += amount;
                }
            }
        }
        return last;
    }

    // n: # of row, m: # of col
    void test(const int input [][MAX_COL], int n, int m) {
        memset(capa_g, sizeof(capa_g), 0);
        memset(capa_g, sizeof(flow_g), 0);
        const_graph(input, n, m, capa_g);
        //dump(capa_g, endnode(n, m));
        int num_flow = max_flow(capa_g, flow_g, endnode(n, m), 0, endnode(n, m));
        cout << num_flow << endl;
        int last = cnt_last(n, m, capa_g, flow_g, endnode(n, m));
        cout << "number of operation:" << num_flow + last << endl;
    } 
}

void test_a02_05_grid_0() {
    PRINT_FUNC_NAME;
    //a02_05::test_q();
    const int input_0 [][MAX_COL] =  { {1, 3}, {1, 2} };
    a02_05::test(input_0, 2, 2);

    const int input_1 [][MAX_COL] =  { {2, 3, 2, 3}, {1, 2, 1, 1} };
    a02_05::test(input_1, 2, 4);

}