#include <iostream>
#include <random>

using namespace std;

std::random_device rd;

std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 1);

// A given random generator for bit(0 or 1)
int rand_bit() {
    return dis(gen) % 2;
}

int random_gen(int start, int end) {
    int result = 0;
    int cnt = end - start + 1;

    do {
        result = 0;
        for (int i = 0; (1 << i) < cnt; i++) {
            result = (result << i) | rand_bit();
        }
    } while (result >= cnt );
    return result + start;
}

void test_p4_10_random_num_bit_op() {
    cout << " * " << __func__ << endl;

    for (int i = 0; i < 100; i++) {
        cout << random_gen(1, 15) << ", ";
    }
    cout << endl;
}