#include <iostream>
#include <utility/dump.hpp>
#include <ctime>

using namespace std;

namespace p13_00_quick_sort {

    void dump(int d[], int i, int j, bool nl) {
        cout << "{";
        for (; i <= j; i++) {
            cout << d[i] << ", ";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void swap(int d[], int i, int j) {
        int tmp = d[i];
        d[i] = d[j];
        d[j] = tmp;
    }

    int partition(int d[], int start, int end) {
        int pivot = start;
        int sm = start + 1;
        int bg = end;
        while(sm != bg) {
            // '=' equal 조건이 없으면 같은 수가 나열될 때, 무한 루프를 돌게 된다.
            // '{5, 13, 17, 0, 0, 0, 0}' 이런 조건으로 확인할 것
            while((d[sm] <= d[pivot]) && (sm != bg)) {
                sm++;
            }
            while((d[pivot] <= d[bg]) && (sm != bg)) {
                bg--;
            }
            swap(d, sm, bg);
        }
        
        if (d[pivot] > d[bg]) {
            swap(d, pivot, bg);
        }

        return bg;
    }

    void quick_sort(int d[], int start, int end) {
        if (start == end) {
            return;
        }

        int sec_start = partition(d, start, end);
        quick_sort(d, start, sec_start - 1);
        quick_sort(d, sec_start, end);
        return;
    }

    void test(int d[], int sz) {
        quick_sort(d, 0, sz - 1);
        dump(d, 0, sz - 1, true);
    }

    // Sorting은 숫자가 10000 개만 넘어가도 시간이 급증한다.
    #define MAX_DATA 1000
    #define MAX_VAL 10

    void init_data(int d[], int sz) {
        for (int i = 0; i < sz; i++) {
            d[i] = rand() % MAX_VAL;
        }
    }

    bool validate_sorting(int d[], int sz) {
        for (int i = 1; i < sz; i++) {
            if (d[i - 1] > d[i]) {
                return false;
            }
        }
        return true;
    }


    void test_random() {
        srand((unsigned)time(NULL));

        int data[MAX_DATA];
        for (int sz = 1; sz < MAX_DATA; sz++) {
            for (int j = 0; j < 100; j++) {
                init_data(data, sz);
                //dump(data, 0, sz - 1, false);
                //cout << "->";

                quick_sort(data, 0, sz - 1);
                //dump(data, 0, sz - 1, true);

                if (!validate_sorting(data, sz)) {
                    dump(data, 0, sz - 1, true);
                    cout << "test failed" << endl;
                    return;
                }
            }
        }
        cout << "test succeed" << endl;

    }
}

void test_p13_00_quick_sort() {
    PRINT_FUNC_NAME;

    //int data[] = {5, 2, 1, 6, 4, 4};
    //int data[] = {5, 13, 17, 0, 0, 0};
    //int data[] = {5, 13, 17, 0, 0, 0, 0};
    //int data[] = {3, 7, 11, 19};
    //int data[] = {4, 1, 3, 0, 2};
    int data[] = {1, 1, 1, 1, 1, 5, 10, 25};
    p13_00_quick_sort::test(data, sizeof(data)/sizeof(int));

    p13_00_quick_sort::test_random();

}