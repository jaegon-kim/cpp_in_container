#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include "utility/dump.hpp"

using namespace std;

namespace p12_10 {

    
    optional<pair<int, int>> exhaustive_search(const vector<string> & words, vector<bool> & visit, unordered_map<string, pair<int, int>> & map, vector<string> & key_vec, int depth) {

        if (depth == words.size()) {
            //dump_vec(key_vec, true);
            string key = "";
            for (size_t i = 0; i < key_vec.size(); i++) {
                key += key_vec[i];
            }
            //cout << key << endl;

            if (map.find(key) != map.end()) {
                return map[key];
                //cout << "found:" << key << endl;
            }

            return nullopt;
        }

        for (size_t i = 0; i < words.size(); i++) {
            if (visit[i]) {
                continue;
            }
            visit[i] = true;
            key_vec.push_back(words[i]);
            auto opt = exhaustive_search(words, visit, map, key_vec, depth + 1);
            if (opt != nullopt) {
                return opt;
            }
            key_vec.pop_back();
            visit[i] = false;
        }

        return nullopt;
    }

    pair<int, int> find_appended_words(const string & phrase, const vector<string> & words) {
        int key_size = 0;
        for (const string & w: words) {
            key_size += w.length();
        }
        //cout << total_size << endl;

        unordered_map<string, pair<int, int>> map;
        for(int i = 0; (i + key_size - 1) < (int) phrase.size(); i++) {
            string key = phrase.substr(i, key_size);
            //cout << key << "," << key.length() << "," << i << "," << (i + key_size) <<  endl;
            map.emplace(key, make_pair(i, i + key_size - 1));
        }

        vector<bool> visit(words.size(), false);
        //dump_vec(visit, true);

        vector<string> key_vec;
        auto opt = exhaustive_search(words, visit, map, key_vec, 0);

        if (opt != nullopt) {
            return opt.value();
        } else {
            return make_pair(-1, -1);
        }
    }

    void test(const string & phrase, const vector<string> & words) {
        auto p = find_appended_words(phrase, words);
        cout << p.first << ", " << p.second << ", " << phrase.substr(p.first, p.second - p.first + 1) << endl;
    }
}


void test_p12_10_find_appended_words() {
    PRINT_FUNC_NAME;
    p12_10::test("amanaplanacanal", vector<string> {"can", "apl", "ana"});
}

