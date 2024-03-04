#include <iostream>
#include "utility/dump.hpp"

#include <random>
#include <utility>
#include <numeric>
#include <unordered_map>

using namespace std;

namespace p12_00 {

    void test_accumulator() {
        std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        int sum = accumulate(begin(v), end(v), 0);
        cout << "sum: " << sum << endl;

        sum = accumulate(begin(v), end(v), 0,
            [] (int accumulated_val, int a) {
                return accumulated_val + a;
            }
        );
        cout << "sum: " << sum << endl;

        std::vector<int> v2{1, 2, 3, 4};

        int mul = accumulate(begin(v2), end(v2), 1, //<-- initial value
            [] (int accumulated_val, int a) {
                return accumulated_val * a;
            }
        );
        cout << "mul: " << mul << endl;
    }

    int string_hash(const string & str, int modulus) {
        const int k_mult = 997;
        return accumulate(begin(str), end(str), 0,
            [k_mult, modulus] (int accumulated_val, char c) {
                return (accumulated_val * k_mult + c) % modulus;
            }
        );
    }

    void test_string_hash() {
        cout << string_hash("Hello World", 5) << endl;
        cout << string_hash("Hello World1", 5) << endl;
        cout << string_hash("Hello World2", 5) << endl;
        cout << string_hash("Hello World", 5) << endl;
    }

    template <typename T>
    void swap(vector<T> &v, size_t i, size_t j) {
        T tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    template <typename T>
    size_t partition(vector<T> &v, size_t start_idx, size_t end_idx, size_t pivot_idx) {

        int pivot = v[pivot_idx];

        size_t s = start_idx; // start_idx ~ (s-1): pivot 보다 작거나 같은 수
        size_t e = end_idx;   // (e+1) ~ end_idx : pivot 보다 큰 수
                              // s ~ e : 확인되지 않은 수

        while(s <= e) { // s == e인 경우가 중요하다. 
            while(v[s] <= pivot && s <= e) {
                s++;
            }
            // v[s]는 pivot 보다 크거나, 확인되지 않은 남은 것이 없음(s > e)
            while(pivot < v[e] && s <= e) {
                e--;
            }

            //dump_vec(v, true);
            //cout << "s: " << s << ", e: " << e << endl;
            //cout << endl;

            // v[e]는 pivot 보다 작거나 같거나, 확인되지 않은 남은 것이 없음(s > e)
            if (s < e) {
                swap(v, s, e);
                if (s == pivot_idx) {
                    pivot_idx = e;
                } else if (e == pivot_idx) {
                    pivot_idx = s;
                }
            }
        }

        swap(v, s - 1, pivot_idx);
        return s - 1;
    }

    void validate_partition(const vector<int> & v) {
        vector<int> a = v;
        int pivot_idx = (a.size() - 1) / 2;
        int pivot = v[pivot_idx];
        size_t p_idx = partition<int>(a, 0, a.size() - 1, pivot_idx);

        bool valid = true;
        size_t idx = 0;

        while(idx <= p_idx) {
            if (a[idx] > pivot) {
                cout << "bigger than pivot" << idx << endl;
                valid = false;
            }
            idx++;
        }
        while(idx < a.size()) {
            if (a[idx] < pivot) {
                cout << "smaller that pivot" << idx << endl;
                valid = false;
            }
            idx++;
        }

        if (!valid) 
        {
            cout << "[ pivot value: " << pivot << "] ";
            dump_vec(v, false);
            cout << "->" ;
            dump_vec(a, false);
            cout << " [ idx: " << p_idx << "] valid : " << (valid ? "true": "false") << endl;
        }
    }

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

    void test_partition() {
        /*
        vector<int> a;
        for (int i = 0; i < 10; i++) {
            for (int j = 1 ; j <= 10; j++) {
                a = gen_random_vec(j);
                validate_partition(a);
            }
        }
        */
        //validate_partition(vector<int> {51, 22, 84, 4, 34, 56} );
        //validate_partition(vector<int> {51, 22, 4, 84, 34, 56} );

        //validate_partition(vector<int> {96, 24, 66, 56, 89, 23, });
        //validate_partition(vector<int> {0, 1, 5, 3, 4, 5});
        validate_partition(vector<int> {3, 1, 2});
    }

    template <typename T>
    void quicksort(vector<T> & v, int start_idx, int end_idx) {
        if (start_idx > end_idx) {
            return;
        }
        int pivot_idx = (start_idx + end_idx) / 2;
        int border_idx = partition(v, start_idx, end_idx, pivot_idx);

        quicksort(v, start_idx, border_idx - 1);
        quicksort(v, border_idx + 1, end_idx);
    }

    void validate_quicksort(const vector<int> & v) {
        vector<int> a = v;
        quicksort(a, 0, a.size() - 1);

        bool valid = true;
        size_t len = a.size();
        if (len > 1) {
            for (size_t i = 1; i < len; i++) {
                if (a[i-1] > a[i]) {
                    valid = false;
                }
            }
        }

        if (!valid) 
        {
            dump_vec(v, false);
            cout << " -> " ;
            dump_vec(a, true);
        }
    }

    void test_quicksort() {
        vector<int> v;
        for (int i = 0; i < 100; i++) {
            for (int j = 1 ; j <= 100; j++) {
                v = gen_random_vec(j);
                validate_quicksort(v);
            }
        }
    }

    void test_anagram(const vector<string> & v) {
        size_t len = v.size();
        unordered_map<string, vector<string>> map;

        for (size_t i = 0 ; i < len; i++) {
            vector<char> ch_v = vector<char>(v[i].begin(), v[i].end());
            quicksort<char>(ch_v, 0, ch_v.size() - 1);

            cout << v[i] ;
            //dump_vec<char>(ch_v, false);
            cout << " -> ";
            //dump_vec<char>(ch_v, false);
            string sorted_str = string(ch_v.begin(), ch_v.end());
            cout << sorted_str << endl;

            if (map.find(sorted_str) == map.end()) {
                map[sorted_str] = vector<string>();
                map[sorted_str].emplace_back(v[i]);
            } else {
                map[sorted_str].emplace_back(v[i]);
            }
        }
        cout << endl;

        for (auto p: map) {
            cout << "Key: " << p.first << " - ";
            dump_vec<string>(p.second, true);
        }

    }

    void test() {
        //test_accumulator();
        //test_string_hash();
        //test_partition();
        //test_quicksort();
        test_anagram(vector<string> {
            "debitcard",
            "elvis",
            "silent",
            "badcredit",
            "lives",
            "freedom",
            "listen",
            "levis",
            "money"
        });
    }
}

void test_p12_00_hashtable_boot() {
    PRINT_FUNC_NAME;
    p12_00::test();   
}