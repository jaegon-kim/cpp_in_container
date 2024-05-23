#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "utility/dump.hpp"
using namespace std;

namespace p16_06 {
    struct Watch {
        Watch(char name, int cost, int weight) : n{name}, c{cost}, w{weight} {}
        char n = 0;
        int c = 0;
        int w = 0;
    };

    void dump_watch_vec(vector<Watch> & v, bool nl) {
        for (auto w: v) {
            cout << "(" << w.n << "-" << w.c << "-" << w.w << "), ";
        }
        if (nl) {
            cout << endl;
        }
    }

    bool compare(const Watch &a, const Watch&b) {
        return a.w < b.w;    
    }


    void pack(vector<Watch> & w_v, int c_i, int c_ws, int c_cs, int & max_cost, vector<Watch> & max_cost_p_v, vector<Watch> & p_v) {

        int ws = 0, cs = 0;

        for (int i = c_i; i < (int) w_v.size(); i++) {

            ws = c_ws + w_v[i].w;  
            if (ws > 130) {
                return;
            }

            cs = c_cs + w_v[i].c;

            p_v.push_back(w_v[i]);

            if (cs > max_cost) {
                //cout << "C:" << cs << ", W: " << ws << ", ";
                //dump_watch_vec(p_v, true);
                max_cost = cs;
                max_cost_p_v = p_v;
            }

            pack(w_v, i + 1, ws, cs, max_cost, max_cost_p_v, p_v);
            p_v.pop_back();
        }
        return;
    }


    vector<int> pack_2(vector<Watch> & w_v, int idx, int a_w, int & r_c) {

        if (idx == (int) (w_v.size() - 1)) {
            vector<int> v;
            if (w_v[idx].w <= a_w) {
                r_c = w_v[idx].c;
                v.push_back(idx);
                return v;
            } else {
                return v;
            }
        }

        int c1 = 0, c2 = 0;
        vector<int> v1, v2;
        if (a_w >= w_v[idx].w) {
            v1 = pack_2(w_v, idx + 1, a_w - w_v[idx].w, c1);
            v1.push_back(idx);
            c1 += w_v[idx].c;
        }

        v2 = pack_2(w_v, idx + 1, a_w, c2);

        if (c1 > c2) {
            r_c = c1;
            return v1;
        } else {
            r_c = c2;
            return v2;
        }
    }

    void test() {
        vector<Watch> w_v{
            // n, c, w
            Watch('A', 65, 20),
            Watch('B', 35, 8),
            Watch('C', 245, 60),
            Watch('D', 195, 55),
            Watch('E', 65, 40),
            Watch('F', 150, 70),
            Watch('G', 275, 85),
            Watch('H', 155, 25),
            Watch('I', 120, 30),
            Watch('J', 320, 65),
            Watch('K', 75, 75),
            Watch('L', 40, 10),
            Watch('M', 200, 95),
            Watch('N', 100, 50),
            Watch('O', 220, 40),
            Watch('P', 99, 10),
        };

        sort(w_v.begin(), w_v.end(), compare);
        //dump_watch_vec(w_v, true);
        int max_cost = 0;
        vector<Watch> max_cost_p_v;
        vector<Watch> p_v;

        pack(w_v, 0, 0, 0, max_cost, max_cost_p_v, p_v);
        cout << "Max cost packing (with pack ): ";
        dump_watch_vec(max_cost_p_v, true);

        int r_c = 0;
        vector<int> r_v = pack_2(w_v, 0, 130, r_c);
        cout << "Max cost packing (with pack2): ";
         for (auto e: r_v) {           
            cout << "(" << w_v[e].n << "-" << w_v[e].c << "-" << w_v[e].w << "), ";
        }
        cout << endl;

    }
}

void test_p16_06_back_pack() {
    p16_06::test();
}