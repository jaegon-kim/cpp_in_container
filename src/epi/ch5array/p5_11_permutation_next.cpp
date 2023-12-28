#include <iostream>
#include <vector>
#include <deque>

using namespace std;

namespace p5_11 {

    template <typename T>
    void dump(const T & v, bool nl) {
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

    template <typename T>
    void swap(vector<T>& v, int i, int j) {
        T tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    template <typename T>
    void reverse(vector<T>& v, int i, int j) {
        while (i < j) {
            swap(v, i++, j--);
        }
    }

    int partition(vector<int> &v, int start_idx, int end_idx, int pivot_idx) {
        int s = start_idx;
        int b = end_idx;
        int pivot = v[pivot_idx];
        while(s <= b) {
            if (v[s] <= pivot) {
                s++;
            } else if (pivot < v[s]) {
                if (pivot_idx == s) {
                    pivot_idx = b;
                } else if (pivot_idx == b) {
                    pivot_idx = s;
                }
                swap<int>(v, s, b);
                b--;
            }
        }
        swap<int>(v, s - 1, pivot_idx);
        return s - 1;
    }

    void quick_sort(vector<int> &v, int start_idx, int end_idx) {
        if (start_idx >= end_idx) {
            return;
        }
        int pivot_idx = partition(v, start_idx, end_idx, start_idx + (end_idx - start_idx + 1)/2);
        quick_sort(v, start_idx, pivot_idx - 1);
        // pivot_idx;
        quick_sort(v, pivot_idx + 1, end_idx);
    }

    bool visit(vector<int>& s, vector<bool>& visited, vector<int>& p, size_t depth, bool& get_next, deque<int>& np) {
        size_t len = s.size();

        for (size_t i = 0; i < len; i++) {

            if (visited[i]) {
                continue;
            }

            visited[i] = true;
            np.emplace_back(s[i]);

            if (get_next) {

                if (depth == (len - 1)) {
                    return true;
                } else {
                    visit(s, visited, p, depth + 1, get_next, np);
                    return true;
                }

            } else {
                if (s[i] == p[depth]) {

                    if (depth == (len - 1)) {
                        get_next = true;
                        //cout << "found "; dump<deque<int>>(np, true);

                        visited[i] = false;
                        np.pop_back();
                        return false;

                    } else {
                        if (visit(s, visited, p, depth + 1, get_next, np)) {
                            return true;
                        }
                    }
                }
            }

            visited[i] = false;
            np.pop_back();
        }
        return false;
    }

    deque<int> next_permutation_with_sort(vector<int>& p) {
        //cout << "org   : "; dump<vector<int>>(p, true);
        vector<int> s = p; // copy for sorting
        size_t len = s.size();

        quick_sort(s, 0, len - 1);
        //cout << "sorted: "; dump<vector<int>>(s, true);
        vector<bool> visited(len, false);
        bool get_next = false;
        deque<int> np(0);
        visit(s, visited, p, 0, get_next, np);
        return np;
    }

    void next_permutation_o_n(vector<int>& p) {
        int len = p.size();
        if (len < 2) {
            return;
        }

        int h = -1;
        for (int i = len - 2; i >= 0; i--) {
            if (p[i] < p[i + 1]) {
                h = i;
            } 
        }

        if (h == -1) {
            return p.clear();
        }

        int min_idx = h + 1;
        for (int j = h + 1; j < len; j++) {
            if ((p[h] < p[j]) && (p[j] < p[min_idx])) {
                min_idx = j;
            }
        }
        swap<int>(p, h, min_idx);
        reverse<int>(p, h + 1, len - 1);
    }

    void test_permutation_next(const vector<int>& v) {
        cout << "original      : "; dump<vector<int>>(v, true);
        vector<int> nv = v;
        deque<int> next = next_permutation_with_sort(nv);
        cout << "next(with sort): "; dump<deque<int>>(next, true);

        nv = v;
        next_permutation_o_n(nv);
        cout << "next(with o(N)): "; dump<vector<int>>(nv, true);
    }
}

void test_p5_11_permutation_next() {
    cout << " * " << __func__ << endl;

    p5_11::test_permutation_next(vector<int>{1, 0, 3, 2});
    p5_11::test_permutation_next(vector<int>{6, 2, 1, 5, 4, 3, 0});
    p5_11::test_permutation_next(vector<int>{3, 2, 1, 0});

}