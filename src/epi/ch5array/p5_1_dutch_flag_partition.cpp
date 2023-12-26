#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;


void swap(vector<int> & v, int i, int j) {
    int tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
}

vector<int> & sort_even_odd(vector<int> & a) {
    size_t len = a.size();
    size_t o = len - 1;
    for (size_t e = 0; e < o; ) {
        if ((a[e] % 2) == 0) {
            // even
            e++;
        } else {
            // odd
            swap(a, e, o--);
        }
    }
    return a;
}

void dump(const vector<int> & a) {
    cout << " {";
    for (const int &v: a) {
        cout << v << ", ";
    }
    cout << "}" << endl;
}

// O(n^2) partition
vector<int> & partition_1(size_t pivot_idx, vector<int> & a) {
    int len = a.size();
    int pivot = a[pivot_idx];

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (a[j] < pivot) {
                swap(a, i, j);
                break;
            }
        }
    }

    for (int i = len - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (pivot < a[j]) {
                swap(a, i, j);
                break;
            }
        }
    }
    return a;
}

// More optimized
vector<int> & partition_2(size_t pivot_idx, vector<int> & a) {
    int len = a.size();
    int pivot = a[pivot_idx];
    int smaller = 0;      // pivot 보다 작은 값이 저장되는 index
    int bigger = len - 1; // pivot 보다 큰 값이 저장되는 index

    for (int j = smaller + 1; j < len; j++) {
        if (a[j] < pivot) {
            swap(a, smaller++, j);
            j = smaller + 1; // 이것이 없으면, a[smaller]가 pivot 보다 작은 경우가 
                             // swap되어 뒤(a[j])로 가고 확인되지 않는다.
                             // smaller index 뒤에는 pivot 값보다 작은 값들이 들어오지만
                             // 놓치는 값이 발생한다.
        }
    }

    for (int j = bigger - 1; j >= 0; j--) {
        if (pivot < a[j]) {
            swap(a, bigger--, j);
            j = bigger - 1; // 이것이 없으면, a[bigger]가 pirvot 보다 큰 경우가
                            // swap 되어 앞(a[j])로 가고 확인되지 않는다.
        }
    }
    return a;
}

// Most Fast
vector<int> & partition_3(size_t pivot_idx, vector<int> & a) {
    int len = a.size();
    int pivot = a[pivot_idx];
    int smaller = 0;
    int bigger = len;

    for (int i = smaller; i < bigger; ) {
        if (a[i] < pivot) {
            swap(a, i++, smaller++);
        } else if (a[i] == pivot) {
            i++;
        } else {
            swap(a, i, --bigger);
        }
    }

    return a;
}

vector<int> & partition_4(size_t pivot_idx, vector<int> & v) {
    int pivot = v[pivot_idx];
    int len = v.size();
    int s = 0;
    int b = len -1;

    while (s <= b) {
        if (v[s] <= pivot) {
            s++;
        } else {
            swap(v, s, b--);
        }
    }
    return v;
}



void test_partition(size_t pivot_idx, const vector<int> & a, 
                            vector<int> & func(size_t, vector<int> &)) {
    vector <int> b = a;
    b = func(pivot_idx, b);

    size_t len = b.size();
    int pivot = a[pivot_idx];
    bool p = false;
    bool chck_rslt = true;

    // check paritition
    for (size_t i = 0; i < len; i++) {
        if (!p) {
            if (b[i] > pivot) {
                p = true;
            }
        } else {
            if (b[i] < pivot) {
                chck_rslt = false;
                break;
            }
        }
    }

    cout << "[" << (chck_rslt?"sucess" : "failure") << "] " << "pivot: " << a[pivot_idx] << "(idx: "<< pivot_idx << ") " << endl;
    dump(a);
    dump(b);
}

namespace p5_1 {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 99);

    vector<int> gen_random_vec(size_t len) {
        vector <int> v;
        for (size_t i = 0 ; i < len; i++) {
            int r = dis(gen);
            v.emplace_back(r);
        }
        // expecting 'copy elision'
        return v;
    }
}


void test_p5_1_dutch_flag_partition() {
    cout << " * " << __func__ << endl;

    vector<int> a = {3, 6, 2, 1, 2, 3, 9, 4};
    cout << "size: " << a.size() << endl;
    dump(a);
    a = sort_even_odd(a);
    dump(a);

    cout << " * test partition" << endl;

    a = {3, 6, 2, 1, 2, 3, 9, 4};
    test_partition(5, a, partition_1);
    test_partition(5, a, partition_2);
    test_partition(5, a, partition_3);
    test_partition(5, a, partition_4);

    a = {3, 6, 3, 1, 9};
    test_partition(2, a, partition_1);
    test_partition(2, a, partition_2);
    test_partition(2, a, partition_3);
    test_partition(2, a, partition_4);

    for (size_t i = 0; i < 30; i++) {
        a = p5_1::gen_random_vec(20);
        test_partition(5, a, partition_3);
        test_partition(5, a, partition_4);
    }
}

