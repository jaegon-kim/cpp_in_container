#include <iostream>
#include "utility/dump.hpp"

#include <numeric>

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

    void test() {

        test_accumulator();

        cout << string_hash("Hello World", 5) << endl;
        cout << string_hash("Hello World1", 5) << endl;
        cout << string_hash("Hello World2", 5) << endl;
        cout << string_hash("Hello World", 5) << endl;
 
    }
}

void test_p12_00_hashtable_boot() {
    PRINT_FUNC_NAME;
    p12_00::test();   
}