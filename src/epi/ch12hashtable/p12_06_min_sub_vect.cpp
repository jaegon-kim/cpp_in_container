#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "utility/dump.hpp"

using namespace std;

namespace p12_06 {

    class Indexing {
        public:
            Indexing(const vector<string> & v) {
                size_t len = v.size();
                for (size_t i = 0; i < len; i++) {
                    indexing(v[i], i);
                }
            }

            void indexing(const string & str, int idx) {
                if (map.find(str) == map.end()) {
                    map.emplace(str, unordered_set<int>());
                }
                map[str].emplace(idx); 
            }

            void erase(const string & str, int idx) {
                if (map.find(str) == map.end()) {
                    cout << "not existing " << str << endl;
                    return;
                }
                if (map[str].find(idx) == map[str].end()) {
                    cout << "not existing idx " << str << ", " << idx << endl;
                    return;
                }
                map[str].erase(idx);
                //cout << "erased idx " << str << ", " << idx << endl;
            }

            bool has(const string & str) {
                if (map.find(str) == map.end()) {
                    return false;
                }
                return map[str].size();
            }

            void dump() {
                for (auto & p: map) {
                    cout << p.first << " ";
                    cout << "{";
                    for (auto idx: p.second) {
                        cout << idx << ", ";
                    }
                    cout << "}" << endl;
                }
            }

        private:
            unordered_map<string, unordered_set<int>> map;
    };

    bool has_keyset(Indexing & index, unordered_set<string> & key_set) {
        for (const string & key: key_set) {
            if(!index.has(key)) {
                return false;
            }
        }
        return true;
    }

    pair<int, int> min_sub_vec(const vector<string> & txt, const vector<string> key) {
        Indexing index(txt);
        //index.dump();
        unordered_set<string> key_set;
        for(const string & k: key) {
            key_set.emplace(k);
        }
        size_t len = txt.size();
        int min_s = -1;
        int min_e = txt.size();

        for(size_t s = 0; s < len; s++) {
            for(size_t e = len - 1; e > s; e--) {
                if (!has_keyset(index, key_set)) {
                    if (e < len - 1) {
                        int dis = e + 1 - s;
                        if ((min_e - min_s) > dis) {
                            min_s = s;
                            min_e = e + 1;
                        }
                    }
                    break;
                }
                index.erase(txt[e], e);
            }
            for (size_t e = s + 1; e < len; e++) {
                index.indexing(txt[e], e);
            }
            index.erase(txt[s], s);
        }

        return make_pair(min_s, min_e);
    }

    void test(const vector<string> & txt, const vector<string> & key) {
        auto p = min_sub_vec(txt, key);
        cout << "txt: ";
        dump_vec(txt, true);
        cout << "key: ";
        dump_vec(key, true);
        cout << " - Found min sub: " << p.first << "(" << txt[p.first] << "), " 
                                  << p.second << "(" << txt[p.second] << ")" << endl;
    }
}

void test_p12_06_min_sub_vect() {
    PRINT_FUNC_NAME;
    p12_06::test(
        vector<string> {"A", "B", "A", "D", "E", "A", "G", "C", "H", "E", "J", "K"},
        vector<string> {"A", "E", "C"}
    );

    p12_06::test(
        vector<string> {"A", "B", "A", "D", "E", "A", "G", "C", "H", "E", "J", "K"},
        vector<string> {"A", "B", "C"}
    );

    p12_06::test(
        vector<string> {"apple", "banana", "apple", "apple", "dog", 
                        "cat",   "apple", "dog", "banana", "apple", "cat", "dog"},
        vector<string> {"banana", "cat"}
    );

    p12_06::test(
        vector<string> {"A", "B", "A", "A", "D", 
                        "C", "A", "D", "B", "A", "C", "D"},
        vector<string> {"B", "C"}
    );

}