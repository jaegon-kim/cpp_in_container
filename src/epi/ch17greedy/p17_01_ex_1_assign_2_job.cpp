#include <iostream>
#include <utility/dump.hpp>

using namespace std;

namespace p17_01_ex_1 {

    void dump(int arr[], int s, int e) {
        cout << "{";
        for (int i = s; i <= e; i++) {
            cout << arr[i] << ", ";
        }
        cout << "}" << endl;
    }

    void swap(int arr[], int a, int b) {
        int tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }


    // 2025.02.24 지금까지 구현했던 quick sort 중에 가장 간결한 구현
    // 구현하면서 동작을 생각하는 것 보다, 동작을 정리하고 구현하니 더 깔끔하게 떨어진다.
    // 핵심 아이디어는 왼쪽에서 부터 Pivot 보다 큰 값을 찾고, 오른쪽 부터는 Pivot 보다 작은 값을 찾아서 Swap하는 것이다.
    // Pivot은 첫번째 element
    // s_c : Pivot 값 보다 작은 지 확인하는 위치 (크거나 같으면 b_c 위치와 swap 대상이 된다.)
    // b_c : Pivot 값 swap 보다 큰지 확인하는 위치 (작거나 같으면 s_c 위치와 swap 대상이 된다.)
    // 같은 경우 그냥 swap 하여 알고리즘을 좀더 간결하게 명시할 수 있다.

    // return start idx of 2'nd partition
    int partition(int arr[], int s, int e) {
        int p = s;
        int s_c = p + 1;
        int b_c = e;

        while(s_c != b_c) {
            while (arr[s_c] < arr[p] && s_c < b_c) {
                s_c++;
            }

            while(arr[p] < arr[b_c] && s_c < b_c) {
                b_c--;
            }
            swap(arr, s_c, b_c);
        }

        if (arr[s_c] < arr[p]) {
            swap(arr, s_c, p);
        }

        return s_c;
    }

    void quick_sort(int arr[], int s, int e) {

        if (s == e) {
            return;
        }

        int sec_s = partition(arr, s, e);
        quick_sort(arr, s, sec_s - 1);
        quick_sort(arr, sec_s, e);
    }

    int assign(int jobs[], int s, int e) {
        int max = 0;
        while (s < e) {
            cout << " - (" << jobs[s] << ", " << jobs[e] << ")" << endl;
            int job_time = jobs[s] + jobs[e];
            if (max < job_time) {
                max = job_time;
            }
            s++;
            e--;
        }

        return max;
    }

    void test(int jobs[], int s, int e) {
        quick_sort(jobs, s, e);
        dump(jobs, s, e);
        int max = assign(jobs, s, e);
        cout << "max job time: " << max << endl;
    }

}

void test_p17_01_ex_1_assign_2_job() {
    PRINT_FUNC_NAME;
    int jobs[] = {5, 2, 1, 6, 4, 4};
    //int jobs[] = {3, 6, 2, 1, 2, 3, 9, 4};
    //int jobs[] = {1, 0, 3, 2};
    //int jobs[] = {6, 2, 1, 5, 4, 3, 0};
    //int jobs[] = {51, 22, 84, 4, 34, 56};
    //int jobs[] = {51, 22, 4, 84, 34, 56};
    //int jobs[] = {96, 24, 66, 56, 89, 23, };
    //int jobs[] = {0, 1, 5, 3, 4, 5};    
    //int jobs[] = {3, 2, 1, 0};

    int e = sizeof(jobs)/sizeof(int) - 1;
    cout << "number of jobs : " << e + 1 << endl;
    p17_01_ex_1::test(jobs, 0, e);
}