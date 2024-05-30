#include <iostream>
#include <vector>
#include <list>
#include "utility/dump.hpp"

using namespace std;

namespace p16_09 {

    template <typename T>
    void dump_cache(const std::vector<T> & v, bool nl) {
        std::cout << "{";
        size_t len = v.size();
        for (size_t i = 0; i < len; i++) {
            if (v[i] == 0xffffffff) {
                //std::cout << "-, ";
                printf("  , ");
            } else {
                //std::cout << v[i] << ", ";
                printf("%2u, ", (unsigned int) v[i]);
            }
        }
        std::cout << "}";
        if (nl) {
            std::cout << std::endl;
        }
    }

    list<size_t> traverse_b(bool turn_b, const vector<int> & v, size_t s, size_t e, int & ret, vector<vector<size_t>> & b_cache) {

        if (s == e) {
            list<size_t> p;
            p.push_front(s);
            b_cache[s][e] = s;
            ret = v[s];
            return p;
        }

        int l, r;
        list<size_t> l_path = traverse_b(!turn_b, v, s + 1, e, l, b_cache);
        list<size_t> r_path = traverse_b(!turn_b, v, s, e - 1, r, b_cache);

        if (turn_b) {
            l += v[s];
            r += v[e];
        }

        if (l > r) {
            if (turn_b) {
                l_path.push_front(s);
                b_cache[s][e] = s;
                //cout << "(" << s << ", " << e << "): " << s << ", ";
            }
            ret = l;
            return l_path;
        } else {
            if (turn_b) {
                r_path.push_front(e);
                b_cache[s][e] = e;
                //cout << "(" << s << ", " << e << "): " << e << ", ";
            }
            ret = r;
            return r_path;
        }
    }

    pair<list<size_t>, list<size_t>> game(bool turn_a, const vector<int> & v, size_t s, size_t e, int & ret, vector<vector<size_t>> & cache_b, int depth) {

        pair<list<size_t>, list<size_t>> p = make_pair(list<size_t>(), list<size_t>());

        if (s == e) {
            //cout << "b(" << depth << ")-" << s << ", ";
            p.second.push_front(s);
            ret = 0;
            return p;
        }

        if (turn_a) {
            int l, r;
            //cout << "a(" << depth << ")-" << s << ", ";
            auto l_path = game(!turn_a, v, s + 1, e, l, cache_b, depth + 1);
            //cout << endl;
            //cout << "a(" << depth << ")-" << e << ", ";
            auto r_path = game(!turn_a, v, s, e - 1, r, cache_b, depth + 1);

            l += v[s];
            r += v[e];

            if (l > r) {
                ret = l;
                l_path.first.push_front(s);
                return l_path;
            } else {
                ret = r;
                r_path.first.push_front(e);
                return r_path;
            }
        } else {
            list<size_t> tmp_b_path;
            if (cache_b[s][e] == 0xffffffff) {
                //cout << "Invalid (" << s << ", " << e << "): " << e << ", " << endl;
                return p;
            }

            if (cache_b[s][e] == s) {
                //cout << "b(" << depth << ")-" << s << ", ";
                auto l_path = game(!turn_a, v, s + 1, e, ret, cache_b, depth + 1);
                l_path.second.push_front(s);
                return l_path;
            } else {
                //cout << "b(" << depth << ")-" << e << ", ";
                auto r_path = game(!turn_a, v, s, e - 1, ret, cache_b, depth + 1);
                r_path.second.push_front(e);
                return r_path;
            }
        }
    }


    void test(const vector<int> & v) {

        cout << endl;
        cout << "Game Coin list : ";
        dump_vec(v, true);

        vector<vector<size_t>> cache_b(v.size(), vector<size_t>(v.size(), 0xffffffff));
        int r_b;
        traverse_b(false, v, 0, v.size() - 1, r_b, cache_b);
      
        cout << "B's best choice for cases (row: start idx, column: end idx, value: selected idx) : " << endl;
        for (auto row: cache_b) {
            dump_cache(row, true);
        }

        int r;
        auto path = game(true, v, 0, v.size() - 1, r, cache_b, 0);
        cout << "A's Score: " << r << endl;
        cout << "A's Selection : ";
        dump_list(path.first, true);
        cout << "B's Selection : ";
        dump_list(path.second, true);

    }
}

void test_p16_09_coin_game() {
    PRINT_FUNC_NAME;
    p16_09::test(vector<int>{5, 25, 10, 1});
    p16_09::test(vector<int>{10, 25, 5, 1, 10, 5});
    p16_09::test(vector<int>{25, 5, 10, 5, 10, 5, 10, 25, 1, 25, 1, 25, 1, 25, 5, 10});
}
