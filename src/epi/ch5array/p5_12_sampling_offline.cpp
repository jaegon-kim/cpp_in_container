#include <iostream>
#include <vector>
#include <random>

using namespace std;

namespace p5_12 {


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
    vector<T> sampling_offline(vector<T>& v, int k) {

        random_device rd;
        mt19937 gen(rd());

        size_t len = v.size();
        for (int i = 0; i < k; i++) {
            uniform_int_distribution<T> dis(i, len - 1);
            size_t r = dis(gen);
            cout << "r: " << i << endl;
            swap<T>(v, i, r);
        }

        return vector<T>(v.begin(), v.begin() + k);
    }

    void test(const vector<int>& v, int k) {

        vector<int> a = v;
        dump<int>(v, true);
        for (int i = 0 ; i < 1; i++) {
            dump<int>(sampling_offline(a, k), true);
        }

    }

}

void test_p5_12_sampling_offline() {
    cout << " * " << __func__ << endl;

    p5_12::test(vector<int>{3, 7, 5, 11, 2, 8, 13, 14, 16, 17}, 3);

}
