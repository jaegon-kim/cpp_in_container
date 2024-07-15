#include <iostream>
#include <vector>
#include <list>
#include "utility/dump.hpp"
using namespace std;
namespace a02_00 {
    void dump_edge(const int capa[][8], size_t size_r, size_t size_c, const char name[]) {
        for (size_t i = 0; i < size_r; i++) {
            for (size_t j = 0; j < size_c; j++) {
                if (capa[i][j]) {
                    cout << "(" << name[i] << ") --" << capa[i][j] << "--> (" << name[j] << ")" << endl; 
                }       
            }
        }
    }

    void dump_path(const vector<int> & prev_v, int source, int sink, const char name[], bool nl) {
        int p = sink;
        cout << name[p];
        while(p != source) {
            p = prev_v[p];
            cout << "->" << name[p];
        }
        if (nl) {
            cout << endl;
        }
    }

    void bfs(const int capa[][8], int source, int sink, const char name[]) {

        vector<int> prev(8, -1);

        list<int> q;
        q.push_back(source);

        while(q.size()) {

            int here = q.front();
            q.pop_front();

            if (here == sink) {
                cout << "found" << endl;
                dump_path(prev, source, sink, name, true);
                break;
            }

            for (size_t there = 0; there < 8; there++) {
                if (capa[here][there] && prev[there] == -1) {
                    q.push_back(there);
                    prev[there] = here;
                }
            }
        }

        

    }

    void test(const int capa[][8], const char name[]) {
        dump_edge(capa, 8, 8, name);
        bfs(capa, 0, 7, name);
    }
}

void test_a02_00_bfs_queue() {
    PRINT_FUNC_NAME;
    const char name[] = {'s', 'a', 'b', 'c', 'd', 'e', 'f', 't' };    
    const int capa[][8] = {
            /* s, a, b, c, d, e, f, t */
       /* s*/ {0, 3, 4, 5, 0, 0, 0, 0,},
       /* a*/ {0, 0, 0, 0, 1, 3, 0, 0,},
       /* b*/ {0, 0, 0, 0, 0, 2, 0, 0,},
       /* c*/ {0, 0, 0, 0, 0, 0, 7, 0,},
       /* d*/ {0, 0, 0, 0, 0, 0, 0, 3,},
       /* e*/ {0, 0, 0, 0, 0, 0, 0, 5,},
       /* f*/ {0, 0, 0, 0, 0, 0, 0, 4,},
       /* t*/ {0, 0, 0, 0, 0, 0, 0, 0,},
    };
    a02_00::test(capa, name);
}