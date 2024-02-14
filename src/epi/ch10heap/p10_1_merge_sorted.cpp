#include <iostream>
#include "utility/dump.hpp"

#include <list>
#include <queue>
#include <functional>
#include <memory>

using namespace std;

namespace p10_1 {

    void test() {
        priority_queue<
            shared_ptr<list<int>> ,
            vector<shared_ptr<list<int>>>,
            function<bool (shared_ptr<list<int>>, shared_ptr<list<int>>)>> 
            pq(
                [] (const shared_ptr<list<int>> & v1, const shared_ptr<list<int>> & v2) {
                    return v1->front() >= v2->front();
                }
            );

        shared_ptr<list<int>> l = make_shared<list<int>>();
        l->push_back(3);
        l->push_back(5);
        l->push_back(7);
        pq.emplace(l);

        l = make_shared<list<int>>();
        l->push_back(0);
        l->push_back(6);
        pq.emplace(l);

        l = make_shared<list<int>>();
        l->push_back(0);
        l->push_back(6);
        l->push_back(28);
        pq.emplace(l);

        shared_ptr<list<int>> s = make_shared<list<int>>();

        while(!pq.empty()) {
            shared_ptr<list<int>> ptr = pq.top();
            pq.pop();
            s->push_back(ptr->front());
            ptr->pop_front();
            if (!ptr->empty()) {
                pq.emplace(ptr);
            }
        }
        dump_list<int>(*s, true);
    }
}

void test_p10_1_merge_sorted() {
    PRINT_FUNC_NAME;
    p10_1::test();
}