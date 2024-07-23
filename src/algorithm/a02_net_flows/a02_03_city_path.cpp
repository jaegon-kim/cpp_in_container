#include <iostream>
#include <cstring>
#include "utility/dump.hpp"
using namespace std;

// Finding the max number of path between 2 cities 
//    https://www.acmicpc.net/problem/17412
//    https://blog.naver.com/kks227/220804885235

#define MAX_N 1024

namespace a02_03 {
    
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

            void dump() {
                cout << "front: " << front_idx << ", back: " << back_idx << "(" << size() << "/" << capa() << ") {";
                for (size_t i = 0; i < N; i++) {
                    cout << buf[i] << ", ";
                }
                cout << "}" << endl;
            }

            void push(T v) {
                if (size() == capa()) {
                    cout << "queue is full" << endl;
                    return;
                }
                buf[front_idx] = v;
                front_idx = (front_idx + 1) % N;
            }

            T pop() {
                if (!size()) {
                    cout << "queue is empty" << endl;
                    return buf[back_idx];
                }
                size_t r_idx = back_idx;
                back_idx = (back_idx + 1) % N;
                return buf[r_idx];
            } 

        private:
            size_t front_idx = 0; // loc to push
            size_t back_idx = 0;  // loc to pop
            T buf[N];
    };


    void test_q() {
        Q<int, 3> q;
        q.dump();
        cout << "push 1, 2, 3, 4" << endl;
        q.push(1); q.dump();
        q.push(2); q.dump();
        q.push(3); q.dump();
        q.push(4); q.dump();
        cout << "pop 1, 2, 3, 4" << endl;
        q.pop(); q.dump();
        q.pop(); q.dump();
        q.pop(); q.dump();
        q.pop(); q.dump();
        cout << "push pop 5" << endl;    
        q.push(5); q.dump();
        q.pop(); q.dump();
        cout << "push pop 6" << endl;    
        q.push(6); q.dump();
        q.pop(); q.dump();
        cout << "push pop 7" << endl;    
        q.push(7); q.dump();
        q.pop(); q.dump();
        cout << "push pop 8" << endl;    
        q.push(8); q.dump();
        q.pop(); q.dump();


    }

    void dump_arr(int arr[][MAX_N], int n) {
        for (int i = 1; i <= n; i++) {
            cout << "{";
            for (int j = 1; j <= n; j++) {
                cout << arr[i][j] << ", ";
            }
            cout << "}" << endl;
        }
    }

    int capa_g[MAX_N][MAX_N];
    int flow_g[MAX_N][MAX_N];
    int prev_g[MAX_N][MAX_N];

    void const_graph(const int input[][MAX_N], int capa[][MAX_N], int p) {
        for (int i = 0; i < p; i++) {
            capa[input[i][0]][input[i][1]] = 1;
        }
    }

    int bfs(int capa[][MAX_N], int flow[][MAX_N], int n, int prev[], int from, int to) {
        for (int i = 1; i <= n; i++) {
            prev[i] = -1;
        }

        Q<int, 1024> q;
        q.push(from);

        int min_amount = 0x7FFFFFFF;
        for (int i = 0; q.size() && prev[to] == -1; i++) {
            int c = q.pop();
            for (int j = 1; j <= n; j++) {
                if (c == j) {
                    continue;
                }
                if (prev[j] != -1) {
                    continue;
                }
                int amount = capa[c][j] - flow[c][j];
                if (amount <= 0) {
                    continue;
                }
                prev[j] = c;
                q.push(j);
                
                if (amount < min_amount) {
                    min_amount = amount;
                }
                if (j == to) {
                    return min_amount;
                }
            }
        }
        return 0;
    }

    int max_path(int capa[][MAX_N], int flow[][MAX_N], int n, int from, int to) {
        size_t num_path = 0;
        for (size_t i = 0; i < 10; i++) {
            int amount = bfs(capa, flow, n, prev_g[i], from, to);
            if (!amount) {
                break;
            }
            num_path++;
            int c = to;
            while(c!=from) {
                cout << c << "<-";
                int p = prev_g[i][c];
                flow[p][c] += amount;
                flow[c][p] -= amount;
                c = p;
            }
            cout << c << endl;
        }
        return num_path;
    }

    // n: number of vertex, p: number of edge
    void test_max_path(const int input[][MAX_N], int n, int p, int from, int to) {
        PRINT_FUNC_NAME;
        memset(capa_g, 0, sizeof(capa_g));
        memset(flow_g, 0, sizeof(flow_g));
        const_graph(input, capa_g, p);
        //dump_arr(capa_g, n);
        auto r = max_path(capa_g, flow_g, n, from, to);
        cout << "num of path: " << r << endl;
    }    
}


void test_a02_03_city_path() {
    PRINT_FUNC_NAME;
    //a02_03::test_q();
    int input1[][MAX_N] = {
            {1, 3},
            {3, 2},
            {1, 5},
            {5, 4},
            {4, 2}
        };
    a02_03::test_max_path(input1, 5, 5, 1, 2);

    int input2[][MAX_N] = {
            {1, 3},
            {3, 2},
            {1, 4},
            {4, 2},
            {1, 5},
            {5, 6},
            {6, 2},
        };
    a02_03::test_max_path(input2, 6, 7, 1, 2);

    int input3[][MAX_N] = {
            {1, 3},
            {1, 4},
            {3, 5},
            {4, 5},
            {5, 6},
            {5, 7},
            {6, 2},
            {7, 2}
        };
    a02_03::test_max_path(input3, 7, 8, 1, 2);


}