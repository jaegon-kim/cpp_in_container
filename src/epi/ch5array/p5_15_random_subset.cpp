#include <iostream>
#include <random>
#include <vector>
#include <unordered_map>

#include "utility/dump.hpp"

using namespace std;

namespace p5_15 {
 
    void dump_map(const unordered_map<int, int> & h, bool nl) {
        std::cout << "{";

        for (pair<int, int> p: h) {
            std::cout << "(" << p.first << " : " << p.second << "), ";
        }

        std::cout << "}";
        if (nl) {
            std::cout << std::endl;
        }
    }

    void swap(unordered_map<int, int> & h, int i, int j) {
        int tmp = h[i];
        h[i] = h[j];
        h[j] = tmp;
    }

    int get_test_random(int i) {
        switch(i) {
            case 0: return 28;
            case 1: return 42;
            case 2: return 28;
            case 3: return 64;
        }
        return -1;
    }


    vector<int> random_subset(int n, int k) {

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, n - 1);

        unordered_map<int, int> h;

        for (int i = 0; i < k; i++ ) {

            if (h.find(i) == h.end()) {
                h[i] = i;
            }

            int r = dis(gen);
            //int r = get_test_random(i);
            
            if (h.find(r) == h.end()) {
                h[r] = r;
            }    

            swap(h, i, r);
            dump_map(h, true);
        }

        vector<int> r(0);
        for (int i = 0; i < k; i++) {
            r.emplace_back(h[i]);
        }
        return r;
    }

    void test(int n, int k) {

        vector<int> r = random_subset(n, k);
        dump_vec<int>(r, true);

    }

    void test_unordered_map() {
        unordered_map<int, int> h;
        cout << "h.size: " << h.size() << endl;
        h[1] = 1;
        h.insert(make_pair(3, 3));
        h.insert({5, 5});

        cout << "h.size: " << h.size() << endl;

        cout << "for (pair<int, int> p: h)  : " << endl;
        for (pair<int, int> p: h) {
             cout << p.first << ") " << p.second << endl;
        }

        int tmp = h[1];
        h[1] = h[3];
        h[3] = tmp;

        cout << "for (int i = 0; i < 7; i++)  " << endl;
        for (int i = 0; i < 7; i++) {
            cout << i << ") " << h[i] << endl;
        }
        cout << "h.size: " << h.size() << endl;

    }

}

void test_p5_15_random_subset() {
    PRINT_FUNC_NAME;
    //p5_15::test_unordered_map();
    p5_15::test(100, 4);
}