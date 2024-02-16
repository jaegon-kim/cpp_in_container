#include <iostream>
#include "utility/dump.hpp"

#include <vector>
#include <queue>
#include <functional>

using namespace std;

namespace p10_5 {

    vector<float> median(const vector<int> & v) {

        vector<float> med_v;
        size_t len = v.size();
        if (len <= 1) {
            for(size_t i = 0; i < len; i++) {
                med_v.push_back((float)v[i]);
            }
            return med_v;
        }

        priority_queue<int, vector<int>, function<bool (int, int)>>
        max_q([](const int & a, const int & b) {
                return a <= b;
            });

        priority_queue<int, vector<int>, function<bool (int, int)>>
        min_q([](const int & a, const int & b) {
                return a >= b;
            });
        
        max_q.emplace(v[0]);
        med_v.push_back(v[0]);
        //cout << "max_q: " << max_q.size() << endl;
        //cout << "min_q: " << min_q.size() << endl;
        //cout << endl;

        for(size_t i = 1; i < len; i++) {
            if (v[i] <= max_q.top()) {
                if (max_q.size() == min_q.size()) {
                    max_q.emplace(v[i]);
                } else {
                    int tmp = max_q.top();
                    max_q.pop();
                    max_q.emplace(v[i]);

                    min_q.emplace(tmp);                
                }
            } else {
                if (max_q.size() == min_q.size()) {
                    if (v[i] < min_q.top()) {
                        max_q.emplace(v[i]);
                    } else {
                        int tmp = min_q.top();
                        min_q.pop();
                        min_q.emplace(v[i]);

                        max_q.emplace(tmp);
                    }
                } else { // max_q.size() > min_q.size()
                    min_q.emplace(v[i]);
                }
            }
            //cout << "max_q: " << max_q.size() << ", top: " << max_q.top() << endl;
            //cout << "min_q: " << min_q.size() << ", top: " << min_q.top() << endl;
            //cout << endl;

            if (max_q.size() == min_q.size()) {
                med_v.push_back((float)(max_q.top() + min_q.top()) / 2);
            } else {
                med_v.push_back(max_q.top());
            }
        }

        return med_v;
    }

    void test(const vector<int> & v) {
        vector<float> r = median(v);
        dump_vec<float>(r, true);
    }
}

void test_p10_5_realtime_median() {
    PRINT_FUNC_NAME;
    p10_5::test(vector<int> {1, 0, 3, 5, 2, 0, 1});
}
