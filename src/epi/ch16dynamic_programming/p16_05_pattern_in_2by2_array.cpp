#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include "utility/dump.hpp"
using namespace std;

namespace p16_05 {

    string make_key(int i, int j, int c) {
        char buf[256];
        sprintf(buf, "%d-%d-%d", i, j, c);
        return string(buf);
    }

    bool discover_pattern(const vector<vector<int>> & a, const vector<int> & p, size_t c, 
                            vector<pair<int, int>> & n, vector<pair<int, int>> & path, unordered_set<string> & fail_cache) {
                                
        if (c == p.size()) {
            dump_vec_of_pair(path, true);
            return true;
        }

        for (auto e: n) {

            // Is cache better to use ? (It has overhead for sprintf, creasting string, and creating hash from string)
            /*
            if(fail_cache.find(make_key(e.first, e.second, c)) != fail_cache.end()) {
                cout << ".";
                continue;
            }
            */

            vector<pair<int, int>> n_v;
            if ((e.first - 1) >= 0 && a[e.first - 1][e.second] == p[c + 1]) {
                n_v.push_back(make_pair(e.first - 1, e.second));
            } 

            if ((e.second - 1) >= 0 && a[e.first][e.second - 1] == p[c + 1]) {
                n_v.push_back(make_pair(e.first, e.second - 1));
            }

            if ((e.first + 1) < (int) a.size() && a[e.first + 1][e.second] == p[c + 1]) {
                n_v.push_back(make_pair(e.first + 1, e.second));
            }

            if ((e.second + 1) < (int) a[0].size() && a[e.first][e.second + 1] == p[c + 1]) {
                n_v.push_back(make_pair(e.first, e.second + 1));
            }
            path.push_back(e);
            bool r = discover_pattern(a, p, c + 1, n_v, path, fail_cache);
            path.pop_back();

            if (r) {
                return true;
            } else {
                /*
                fail_cache.emplace(make_key(e.first, e.second, c));
                */
            }
        }
        return false;
    }

    void test(const vector<vector<int>> & a, const vector<int> & p) {

        vector<pair<int, int>> n;
        for(size_t i = 0; i < a.size(); i++) {
            size_t j_size = a[i].size();
            for (size_t j = 0; j < j_size; j++) {
                if (a[i][j] == p[0]) {
                    n.push_back(make_pair(i, j));
                }
            }
        }

        vector<pair<int, int>> path;
        unordered_set<string> fail_cache;
        bool r = discover_pattern(a, p, 0, n, path, fail_cache);
        
        cout << "finding pattern ";
        dump_vec(p, false);
        cout << " " << (r? "found" : "not-found") << endl;

    }
}

void test_p16_05_pattern_in_2by2_array() {
    PRINT_FUNC_NAME;
    
    p16_05::test(
        vector<vector<int>> {
            vector<int> {1, 2, 3},
            vector<int> {3, 4, 5},
            vector<int> {5, 6, 7}  
        },
        vector<int> {1, 3, 4, 6}
    );

    p16_05::test(
        vector<vector<int>> {
            vector<int> {1, 2, 3},
            vector<int> {3, 4, 5},
            vector<int> {5, 6, 7}  
        },
        vector<int> {1, 2, 3, 4}
    );

    // this case will use cache
    p16_05::test(
        vector<vector<int>> {
            vector<int> {1, 2, 3, 3, 4},
            vector<int> {3, 4, 2, 5, 6},
            vector<int> {5, 6, 1, 8, 9},
            vector<int> {5, 6, 7, 8, 9},
            vector<int> {5, 1, 2, 3, 9},

        },
        vector<int> {1, 2, 3, 9}
    );
    
}