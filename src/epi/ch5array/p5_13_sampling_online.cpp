#include <iostream>
#include <vector>
#include <random>

using namespace std;

namespace p5_13 {

    template <typename T>
    void dump(const vector<T> &v, bool nl) {
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
    void swap(vector<T> v, int i, int j) {
        T tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    template <typename T>
    vector<T> sampling_online(vector<T>& v, int k) {

        random_device rd;
        mt19937 gen(rd());

        vector<T> s(0);

        int len = v.size();
        if (len < k) {
            return s;
        }

        int i = 0;
        for (i = 0; i < k; i++) {
            s.emplace_back(v[i]);
        }

        for (; i < len; i++) {
            uniform_int_distribution<T> dis(0, i);
            int r = dis(gen);

            if (r < k) {
                s[r] = v[i];
            }
        }

        return s;
    }

    void test(const vector<int>& v, int k) {

        vector<int> a = v;
        dump<int>(v, true);
        for (int i = 0 ; i < 1; i++) {
            dump<int>(sampling_online(a, k), true);
        }

    }


}

void test_p5_13_sampling_online() {
    cout << " * " << __func__ << endl;

    p5_13::test(vector<int>{3, 7, 5, 11, 2, 8, 13, 14, 16, 17}, 3);
}

