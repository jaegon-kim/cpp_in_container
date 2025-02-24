#include <iostream>
#include <vector>
#include <utility>
#include <random>

using namespace std;

namespace p5_8 {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 99);

    vector<int> gen_random_vec(size_t len) {
        vector<int> v;
        for (size_t i = 0; i< len; i++) {
            int r = dis(gen);
            v.emplace_back(r);
        }
        return v;
    }

    void swap(vector<int> & v, int i, int j) {
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    void dump(const vector<int> & a, const int start_idx, const int end_idx, bool nl) {
        cout << " {";
        for (int i = start_idx; i <= end_idx; i++) {
            cout << a[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    // 'test_p17_01_ex_1_assign_2_job'의 quick sort를 참조 할 것. 아래 quick sort구현 보다 더 간결하다 !!

    // O(N) partition 
    int partition(vector<int> & v, int pivot_idx, int start_idx, int end_idx) {
        int pivot = v[pivot_idx];
        //cout << "pivot: " << pivot << "(idx:" << pivot_idx << ")" << endl;

        int s = start_idx;  // start_idx ~ s-1 : pivot 보다 작거나 같은 값들
        int b = end_idx;    // b+1 ~ end_idx : pivot 보다 큰 값들
                            // s ~ b: 확인되지 않은 값들 (이것이 없어져야 한다)         
        while(s <= b) {
            // 작거나 같은 조건이므로, 왼쪽은 최소 한개(pivot)의 element를 갖는다.
            // 오른 쪽은 비어있을 수 있다. 
            if (v[s] <= pivot) {
                s++;
            } else {
                // tracking pivot_idx
                if (s == pivot_idx) {
                    pivot_idx = b;
                } else if (b == pivot_idx) {
                    pivot_idx = s;
                }
                swap(v, s, b--);
            }
        }
        // s - 1 : pivot 보다 작거나 같은 값들의 end index (border)
        // s - 1은 항상 border가 된다. 왜냐하면, 왼쪽은 최소 한개(pivot)의 element를 갖기 때문이다.
        swap(v, s - 1, pivot_idx);
        // s - 1은 pivot 값이 다.
        return s - 1;
    }

    void quicksort(vector<int> & v, int start_idx, int end_idx) {

        if (start_idx >= end_idx) {
            return;
        }
        //dump(v, start_idx, end_idx, true);
        int pivot_idx = start_idx + (end_idx - start_idx + 1)/2;
        int b = partition(v, pivot_idx, start_idx, end_idx);

        // pivot 은 빼고 만든다. pivot 도 포함할 경우 무한 반복할 수 있다.
        quicksort(v, start_idx, b - 1);

        // b 위치에는 pivot 값이 위치한다.

        quicksort(v, b + 1, end_idx);
    }

    void repeat_big_small(vector<int> & v) {
        size_t len = v.size();
        for(size_t i = 0; i < len; i++) {
            if (((i%2) == 0) && ((i+1) < len)) {
                swap(v, i, i+1);
            }
        }

    }

    bool test(vector<int> & a) {
        vector<int> v = a;
        //dump(v, 0, v.size() - 1, true);
        quicksort(v, 0, v.size() - 1);
        //dump(v, 0, v.size() - 1, true);
        //cout << endl;

        size_t len = v.size();
        if (len <= 1) {
            return true;
        }

        for (size_t i = 1; i < len; i++) {
            if (v[i-1] > v[i]) {
                return false;
            }
        }

        repeat_big_small(v);

        return true;
    }

}

void test_p5_8_quicksort_repeat_big_small() {
    cout << " * " << __func__ << endl;

    vector<int> a = {3, 6, 2, 1, 2, 3, 9, 4};
    p5_8::test(a);

    a = {0, 0, 0, 0, 0};
    p5_8::test(a);

    for (int i = 0; i < 1000; i++) {
        a = p5_8::gen_random_vec(100);
        if (!p5_8::test(a)) {
            cout << "Failed with ";
            p5_8::dump(a, 0, a.size()-1, true);
        }
    }

}