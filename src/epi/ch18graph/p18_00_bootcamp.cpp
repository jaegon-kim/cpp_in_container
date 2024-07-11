#include <iostream>
#include "utility/dump.hpp"
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;
namespace p18_00 {
    struct Game {
        string winner;
        string loser;
    };

    void dump_graph(const unordered_map<string, unordered_set<string>> & g, bool nl) {
        for (const auto & p: g) {
            cout << p.first << "->{";
            for (const auto & e: p.second) {
                cout << e << ", ";
            }
            cout << "}" << endl;
        }
        if (nl) {
            cout << endl;
        }
    }

    void dump_list(const list<Game> & l, bool nl) {
        cout << "{";
        for (const auto & e: l) {
            cout << "(" << e.winner << "->" << e.loser << "),";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    unordered_map<string, unordered_set<string>> build_graph(const vector<Game> & v) {
        unordered_map<string, unordered_set<string>> map;
        for (const auto & p: v) {
            if (map.find(p.winner) == map.end()) {
                map.emplace(p.winner, unordered_set<string>());
            }
            map[p.winner].emplace(p.loser);
        }
        return map;
    }

    list<Game> dfs_search(string from, string to, unordered_map<string, unordered_set<string>> & g, 
        unordered_set<string> & visited) {

        if (g.find(from) == g.end()) {
            return list<Game>();
        }
        unordered_set<string> nexts = g[from];
        if (nexts.find(to) != nexts.end()) {
            list<Game> l;
            l.push_front(Game{from, to});
            return l;
        }

        for(const auto & n: nexts) {

            if (visited.find(n) != visited.end()) {
                continue;
            }

            visited.emplace(n);
            auto r = dfs_search(n, to, g, visited);
            visited.erase(n);

            if (r.size()) {
                r.push_front(Game{from, n});
                return r;
            }
        }
        return list<Game>();
    }

    void test_dfs(const vector<Game> & v, string from, string to) {
        unordered_map<string, unordered_set<string>> g = build_graph(v);
        unordered_set<string> visited;
        //dump_graph(g, true);
        auto r = dfs_search(from, to, g, visited);
        dump_list(r, true);
    }
}

void test_p18_00_graph_bootcamp() {
    PRINT_FUNC_NAME;
    vector<p18_00::Game> v{
        {"a", "b"},
        {"b", "c"},
        {"a", "c"},
        {"c", "e"},
        {"b", "k"},
        {"e", "d"},
        {"k", "f"},
        {"k", "i"},
        {"i", "j"},
        {"j", "l"},
        {"l", "i"},
        {"j", "f"},
        {"d", "f"},
        {"d", "h"},
        {"f", "g"},
        {"g", "h"},
        {"m", "n"},
    }; 
    p18_00::test_dfs(v, "a", "h");
    p18_00::test_dfs(v, "l", "h");
    p18_00::test_dfs(v, "a", "a");
    p18_00::test_dfs(v, "h", "a");

}