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
    void swap(vector<T> & v, int i, int j) {
        T tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }


    template <typename T>
    vector<T> sampling_offline(vector<T>& v, int k) {

        random_device rd;
        mt19937 gen(rd());
        //uniform_int_distribution<T> dis(i, len - 1);
        size_t len = v.size();
        uniform_int_distribution<T> dis(0, 99 );
        //cout << "len: " << len << endl;
        //cout << "k  : " << k << endl;

        for (int i = 0; i < k; i++) {
            //T r = dis(gen) % (len - 1 - i) + i;
            T r = dis(gen);
            T t = r % (len - i) + i;

            //cout << i << ") r: " << r << " % " << (len - i) << " = " << t << endl;
            swap<T>(v, i, t);
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

    void test_generate_random() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 99);

        for (int i = 0; i < 100; i++) {
            cout << dis(gen) << ", ";
        }
        cout << endl;
    }

}

void test_p5_12_sampling_offline() {
    cout << " * " << __func__ << endl;

    p5_12::test(vector<int>{3, 7, 5, 11, 2, 8, 13, 14, 16, 17}, 3);

    //5_12::test_generate_random();

}
