#include <iostream>
#include <vector>
#include <deque>


using namespace std;

template <typename T>
void dump(T q, bool nl) {
    cout << "{";
    size_t len = q.size();
    for (size_t i = 0 ; i < len; i++) {
        cout << q[i] << ", ";
    }
    cout << "}";
    if (nl) {
        cout << endl;
    }
}


bool is_prime(unsigned int n) {
    if (n <= 1) { // 0, 1 is not prime
        return false;
    }
    for (unsigned int i = 2; i < n; i++) {
        if ((n % i) == 0) {
            return false;
        }
    }
    return true;
}


deque<int> gen_prime(unsigned int n) {
    vector<bool> num(n + 1, true); // true: prime, false: not prime
    num[0] = false; // unsigned int always has 0

    if (n >= 1) {
        num[1] = false;
    }

    for (unsigned int i = 2; i <= n; i++) {
        if (num[i] && is_prime(i)) {
            for (unsigned j = 2; i * j <= n; j++) {
                num[i * j] = false;
            }
        }
    }
    //dump<vector<bool>>(num, true);
    deque<int> prime_nums(0);
    for (unsigned int i = 0; i < (n + 1); i++ ) {
        if (num[i]) {
            prime_nums.emplace_back(i);
        }
    }

    return prime_nums;
}

void test_gen_prime(unsigned int n) {
    deque<int> p = gen_prime(n);
    dump<deque<int>>(p, true);
}


void test_p5_9_generate_prime() {
    cout << " * " << __func__ << endl;

    test_gen_prime(10);
    test_gen_prime(100);
    test_gen_prime(1000);
}