#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "utility/dump.hpp"

using namespace std;

namespace p12_07 {

    unordered_set<string> make_key_set(const list<string> & key) {
        unordered_set<string> key_set;
        for(const string & k: key) {
            key_set.emplace(k);
        }
        return key_set;
    }

    pair<int, int> min_sub_vec_distil(const vector<string> & txt, const list<string> & key) {

        unordered_set<string> key_set = make_key_set(key);

        vector<pair<int, string>> d_txt;
        size_t txt_len = txt.size();
        for(size_t i = 0; i < txt_len; i++) {
            if (key_set.find(txt[i]) != key_set.end()) {
                d_txt.emplace_back(make_pair(i, txt[i]));
            }
        }
        //dump_vec_of_pair(d_txt, true);
        int min_s = -1;
        int min_e = txt.size();

        size_t d_txt_len = d_txt.size();
        for (size_t s = 0; s < d_txt_len; s++) {
            if (key.front().compare(d_txt[s].second)) {
                continue;
            }

            list<string> ordered_key = key;
            for(size_t e = s; e < d_txt_len; e++) {

                if (!ordered_key.front().compare(d_txt[e].second)) {
                    ordered_key.pop_front();
                }

                if (!ordered_key.size()) {
                    if ((min_e - min_s) > (int) (d_txt[e].first - d_txt[s].first)) {
                        min_e = d_txt[e].first ;
                        min_s = d_txt[s].first ;
                    }
                    break;
                }
            }
        }
        return make_pair(min_s, min_e);
    }


    void test(const vector<string> & txt, const list<string> & key) {
        //auto p = min_sub_vec(txt, key);
        auto p = min_sub_vec_distil(txt, key);

        cout << "txt: ";
        dump_vec(txt, true);
        cout << "key: ";
        dump_list(key, true);
        if ( p.first >= 0 && p.second < (int) txt.size()) {
            cout << " - Found min sub: " << p.first << "(" << txt[p.first] << "), " 
                                    << p.second << "(" << txt[p.second] << ")" << endl;
        }
    }
}

void test_p12_07_min_sub_vect_ordered() {
    PRINT_FUNC_NAME;
    p12_07::test(
        vector<string> {"A", "B", "A", "D", "E", "A", "G", "C", "H", "E", "J", "K"},
        list<string> {"A", "E", "C"}
    );
    cout << endl;
    p12_07::test(
        vector<string> {"A", "B", "A", "D", "E", "A", "G", "C", "H", "E", "J", "K"},
        list<string> {"A", "B", "C"}
    );
    cout << endl;
    p12_07::test(
        vector<string> {"apple", "banana", "apple", "apple", "dog", 
                        "cat",   "apple", "dog", "banana", "apple", "cat", "dog"},
        list<string> {"banana", "cat"}
    );
    cout << endl;
    p12_07::test(
        vector<string> {"A", "B", "A", "A", "D", 
                        "C", "A", "D", "B", "A", "C", "D"},
        list<string> {"B", "C"}
    );

}