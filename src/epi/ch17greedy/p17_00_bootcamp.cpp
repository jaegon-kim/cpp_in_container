#include <iostream>
#include <vector>
#include <unordered_set>
#include <optional>
#include "utility/dump.hpp"
using namespace std;
namespace p17_00 {

    vector<pair<int, int>> has_2sum_with_unordered_map(const vector<int> & v, int s) {
        vector<pair<int, int>> r;
        unordered_map<int, size_t> map;

        vector<int> v2;
        for(size_t i = 0; i < v.size(); i++) {
            v2.push_back(s - v[i]);
            map.emplace(v[i], i);
        }

        //dump_vec(v2, true);
        //dump_map(map, true);


        for(size_t i = 0; i < v2.size(); i++) {
            if (map.find(v2[i]) != map.end()) {
                r.push_back(make_pair(v[i], v2[i]));
            }
        }

        return r;
    }

     vector<pair<int, int>> complete_search(const vector<int> & v, int s) {
        vector<pair<int, int>> r;        
        for (size_t i = 0; i < v.size(); i++) {

            for (size_t j = i + 1; j < v.size(); j++) {
                if ((v[i] + v[j]) == s) {
                    r.push_back(make_pair(v[i], v[j]));
                }
            }
        }
        return r;
    }

    // 불변식을 사용한다. 양쪽 끝에서 시작해서, sum 보다 작으면 왼쪽을 늘리고, 크면 오른쪽을 줄인다. !!
    // 이런 것이 불변 식이다. !!! 
    
    vector<pair<int, int>> using_invariants(const vector<int> & v, int sum) {
        vector<pair<int, int>> r;        
        int s = 0, e = v.size() - 1;

        while(s < (int) v.size() && e >= 0) {
            //cout << v[s] << ", " << v[e] << endl;           
            int t = v[s] + v[e];
            if (t == sum) {
                r.push_back(make_pair(v[s], v[e]));
                break;
            } else if (t < sum) {
                s++;
            } else {
                e--;
            }
        }

        return r;
    }


    void test_has_2sum(const vector<int> & v, int s) {
        auto r = has_2sum_with_unordered_map(v, s);
        dump_vec_of_pair(r, true);

        r = complete_search(v, s);
        dump_vec_of_pair(r, true);

        r = using_invariants(v, s);
        dump_vec_of_pair(r, true);
    }
}

void test_p17_00_bootcamp() {
    PRINT_FUNC_NAME;
    p17_00::test_has_2sum(vector<int> {-2, 1, 2, 4, 7, 11}, 6);
    p17_00::test_has_2sum(vector<int> {-2, 1, 2, 4, 7, 11}, 0);
    p17_00::test_has_2sum(vector<int> {-2, 1, 2, 4, 7, 11}, 13);
    p17_00::test_has_2sum(vector<int> {-2, 1, 2, 4, 7, 11}, 10);


}
