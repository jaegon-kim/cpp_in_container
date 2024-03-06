#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "utility/dump.hpp"

using namespace std;

namespace p12_05 {

    pair<int, int> closest_dup_str(const vector<string> & v) {

        unordered_map<string, pair<int, int>> map;
        int len = v.size();
        for (int i = 0; i < len; i++) {
            if (map.find(v[i]) == map.end()) {
                map.emplace(v[i], make_pair(-1 * len, i)); // pair(prior, later)
            } else {
                auto p = map[v[i]];
                if ((p.second - p.first) > (i - p.second)) {
                    map[v[i]] = make_pair(p.second, i);
                } 
            }
        }

        int min_d = len;
        pair<int, int> closet;
        for (auto p: map) {
            int d = p.second.second - p.second.first;
            if (d <= min_d) {
                min_d = d;
                closet = p.second;
            }
            //cout << p.first << ": " << p.second.first << ", " << p.second.second << " (" << d << ")" << endl;
        }

        return closet;
    }

    void test() {
        const vector<string> v = vector<string> {
            "All", "work", "and", "no", "play", "makes", "for",
            "no", "work", "no", "fun", "and", "no", "results"
        };
        pair<int, int> closest = closest_dup_str(v);

        cout << "closet: " << v[closest.first] << " (" << closest.first << ") , " 
                            << v[closest.second] << " (" << closest.second << ")" << endl; 
    }
}

void test_p12_05_closest_dup_str() {
    PRINT_FUNC_NAME;
    p12_05::test();
}