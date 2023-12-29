#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

namespace p5_12 {
    template <typename T>
    void dump(const vector<T> &v, bool nl);

    template <typename T>
    vector<T> sampling_offline(vector<T>& v, int k);
}

namespace p5_14 {

    void test(int n) {

        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        cout << "permutation: "; p5_12::dump<int>(p, true);
        vector<int> r = p5_12::sampling_offline<int>(p, p.size());
        cout << "random perm: "; p5_12::dump<int>(p, true);
    }
}


void test_p5_14_random_permutation() {
    cout << " * " << __func__ << endl;

    p5_14::test(10);

}