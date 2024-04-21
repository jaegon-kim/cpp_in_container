#include <iostream>
#include <list>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p15_04 {

    void permutation(list<int> & l, vector<int> & path) {

        if (!l.size()) {
            dump_vec(path, true);
            return;
        }

        size_t len = l.size();
        for(size_t c = 0; c < len; c++) {
            int n = l.front();
            l.pop_front();
            path.push_back(n);
            permutation(l, path);
            path.pop_back();
            l.push_back(n);
        }
    }

    void test(const list<int> & num_list) {
        list<int> l = num_list;
        vector<int> path;
        permutation(l, path);
    }
}

void test_p15_04_permutation() {
    PRINT_FUNC_NAME;
    p15_04::test(list<int> {2, 3, 5, 7});
}