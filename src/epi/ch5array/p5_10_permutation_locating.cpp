#include <iostream>
#include <vector>

using namespace std;

namespace p5_10 {

    template <typename T>
    void dump(const T v, bool nl) {
        cout << "{";
        size_t len = v.size();
        for (size_t i = 0; i < len; i++) {
            cout << v[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void locate_with_new_space(vector<char> &p, vector<int> &loc) {
        size_t len = p.size();
        vector<char> n(len);
        for (size_t i = 0; i < len; i++) {
            n[loc[i]] = p[i];
        }
        for (size_t i = 0; i < len; i++) {
            p[i] = n[i];
        }
    }

    template <typename T>
    void swap(vector<T> & v, int i, int j) {
        T tmp;
        tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    void locate_with_swap(vector<char> &p, vector<int> &l) {
        int len = p.size();
        for (int i = 0; i < len;) {
            int loc = l[i]; 
            if (i == loc) {
                i++;
            } else {
                swap<char>(p, i, loc);
                swap<int>(l, i, loc);
            }
        }
    }

    void test(const vector<char> &p, const vector<int> &loc) {
        dump<vector<char>>(p, false);
        dump<vector<int>>(loc, true);
        vector<char> np = p;
        vector<int> nloc = loc;
        locate_with_new_space(np, nloc);
        dump<vector<char>>(np, true);

        np = p;
        nloc = loc;
        locate_with_swap(np, nloc);
        dump<vector<char>>(np, true);
    }
}

void test_p5_10_permutation_locating() {
    cout << " * " << __func__ << endl;

    p5_10::test(vector<char>{'a', 'b', 'c', 'd'}, vector<int>{2, 0, 1, 3});
}

