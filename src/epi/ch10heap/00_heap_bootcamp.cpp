#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include "utility/dump.hpp"

using namespace std;

namespace p10 {
    vector<string> topk(size_t k, vector<string>::const_iterator stream_begin,
                                const vector<string>::const_iterator stream_end) {
        priority_queue<
            string,
            vector<string>,
            function<bool (string, string)>> 
            min_heap(
                [] (const string& a, const string& b) {
                    return size(a) >= size(b);
                }
            );

        while(stream_begin != stream_end) {
            //cout << *stream_begin << ", ";
            min_heap.emplace(*stream_begin);
            if (size(min_heap) > k) {
                min_heap.pop();
            }
            stream_begin = next(stream_begin);
        }
        //cout << endl;
        vector<string> result;

        while(!empty(min_heap)) {
            result.emplace_back(min_heap.top());
            min_heap.pop();
        }
        return result; 
    }

    void test() {
        vector<string> v = {"hello", "world", "you", "can", "enlarge", "the", "world", "hellohellohello"};
        vector<string> kv = topk(3, v.begin(), v.end());
        dump_vec(kv, true);
    }
}

void test_p10_heap_bootcamp() {
    PRINT_FUNC_NAME;
    p10::test();
}