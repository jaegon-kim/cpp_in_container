#include <iostream>
#include <list>
#include <vector>
#include "utility/dump.hpp"

using namespace std;

namespace p13_11 {

    list<pair<int, int>> sort(const list<pair<int, int>> & l) {
        
        list<pair<int, int>> sl;
        for(auto & p : l) {
            if( sl.empty()) {
                sl.push_back(p);
                continue;
            }
            auto iter = sl.begin();
            for( ;iter != sl.end(); iter++) {
                if ((*iter).first > p.first) {
                    break;
                }
            }
            sl.insert(iter, p);
        }
        return sl;
    }

    void test(const list<pair<int, int>> & l) {
        auto sl = sort(l);
        dump_list_of_pair(sl, true);
    }
}

void test_p13_11_list_safe_sort() {
    PRINT_FUNC_NAME;
    p13_11::test(list<pair<int, int>> {{6, 0}, {5, 0}, {6, 1}, {7, 0}, {8, 0}});

}
