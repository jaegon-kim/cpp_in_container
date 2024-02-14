#include <iostream>
#include "utility/dump.hpp"

#include <vector>
#include <queue>
#include <list>
#include <memory>
#include <functional>

using namespace std;

namespace p10_2 {
    vector<int> sort_k_inc_dec(const vector<int> & v) {

        vector <int> sorted_v;
        size_t len = v.size();
        if (!len) {
            return sorted_v;
        }
        if (len < 1) {
            sorted_v.push_back(v[0]);
            return sorted_v;
        }

        priority_queue<
            shared_ptr<list<int>>,
            vector<shared_ptr<list<int>>>,
            function<bool (shared_ptr<list<int>>, shared_ptr<list<int>>)>
        > pq(
            [] (const shared_ptr<list<int>> & l1, const shared_ptr<list<int>> &l2){
                return l1->front() >= l2->front();
            }
        );

        bool is_inc = (v[0] < v[1] ? true : false);
        shared_ptr<list<int>> sorted_list = make_shared<list<int>>();
        size_t i = 1;
        for (; i < len; i++) {
            if (is_inc) { // increasing previously
                sorted_list->push_back(v[i-1]);
                if (v[i-1] > v[i]) { // to be decreased
                    // emplace
                    dump_list<int>(*sorted_list, true);
                    pq.emplace(sorted_list);
                    sorted_list = make_shared<list<int>>();
                    is_inc = false;
                }
            } else { // descreasing previously
                sorted_list->push_front(v[i-1]);
                if (v[i-1] < v[i]) { // to be increased
                    // emplace
                    dump_list<int>(*sorted_list, true);
                    pq.emplace(sorted_list);
                    sorted_list = make_shared<list<int>>();
                    is_inc = true;
                }
            }
        }

        if (is_inc) { // increasing previously
            sorted_list->push_back(v[i-1]);
        } else { // descreasing previously
            sorted_list->push_front(v[i-1]);
        }
        dump_list<int>(*sorted_list, true);
        pq.emplace(sorted_list);

        while(!pq.empty()) {
            shared_ptr<list<int>> l = pq.top();
            pq.pop();
            //cout << l->front() << ", ";
            sorted_v.push_back(l->front());
            l->pop_front();
            if (!l->empty()) {
                pq.emplace(l);
            }
        }

        return sorted_v;
    }

    void test(const vector<int> & v) {
        vector<int> r = sort_k_inc_dec(v);
        dump_vec(r, true);
    }

}

void test_p10_2_sort_k_inc_dec_array() {
    PRINT_FUNC_NAME;
    p10_2::test(vector<int> {57, 131, 493, 294, 221, 339, 418, 452, 442, 190});
}
