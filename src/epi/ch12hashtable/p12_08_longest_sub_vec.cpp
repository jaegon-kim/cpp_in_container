#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "utility/dump.hpp"

using namespace std;


namespace p12_08 {

    template <typename T>
    pair<int, int> longest_sub_vec(const vector<T> & vec) {
        int len = vec.size();
        int max_s = -1;
        int max_e = -1;
        for (int s = 0; s < len; s++) {
            unordered_set<T> set;
            set.emplace(vec[s]);

            for (int e = s + 1; e < len; e++) {
                if (set.find(vec[e]) != set.end()) {
                    if ((max_e - max_s) < (e - 1 - s)) {
                        max_e = e - 1;
                        max_s = s;
                    }
                    //cout << s << ", " << e << endl;
                    break;
                }                               
                set.emplace(vec[e]);
            }
        }
        return make_pair(max_s, max_e);
    }

    template <typename T>
    pair<int, int> longest_sub_vec_o_n(const vector<T> & vec) {
        int len = vec.size();

        unordered_map<char, int> map;

        int s = 0;
        map.emplace(vec[s], s);
        int max_s = 0;
        int max_e = 0;
        // s ~ e는 유일한 요소로만 구성된 부분 배열임을 보장한다.
        // 다음에 추가되는 원소가 
        //    기존에 있다면, 시작 인덱스를 다음 위치로 옮긴다
        //    기존에 없다면, 단순히 끝 인덱스를 옮긴다 (목표는 가장 긴 Vector를 찾는 것이다)
        for (int e = 1; e < len; e++) {
            if (map.find(vec[e]) != map.end()) {
                s = map[vec[e]] + 1;
                map.erase(vec[e]);
            } else {
                map.emplace(vec[e], e);
                if ((max_e - max_s) < (e - s)) {
                    max_e = e;
                    max_s = s;
                }
            }
        }

        return make_pair(max_s, max_e);
    }

    // 중복되지 않은 문자로 구성된 가장 긴 부분 Vector
    void test(const vector<char> & vec) {
        pair<int, int> p = longest_sub_vec<char>(vec);
        cout << p.first <<"(" << vec[p.first] << ")" << ", " << p.second <<"(" << vec[p.second] << ")" << endl;
        p = longest_sub_vec_o_n<char>(vec);
        cout << p.first <<"(" << vec[p.first] << ")" << ", " << p.second <<"(" << vec[p.second] << ")" << endl;
    }
}

void test_p12_08_longest_sub_vec() {
    PRINT_FUNC_NAME;
    p12_08::test(vector<char> {'f', 's', 'f', 'e', 't', 'w', 'e', 'n', 'w', 'e'});
}