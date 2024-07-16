#include <iostream>
#include "utility/dump.hpp"
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;
namespace p18_04 {

    struct LockDependency {
        string source;
        string dest;
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

    void dump_list(const list<LockDependency> & l, bool nl) {
        cout << "{";
        for (const auto & e: l) {
            cout << "(" << e.source << "->" << e.dest << "),";
        }
        cout << "}";
        if (nl) {
            cout << endl;
        }
    }

    void dump_indent(int depth) {
        //cout << " ";
        for (int i = 0; i < depth; i++) {
            cout << "   ";
        }
    }

    unordered_map<string, unordered_set<string>> build_graph(const vector<LockDependency> & v) {
        unordered_map<string, unordered_set<string>> map;
        for (const auto & p: v) {
            if (map.find(p.source) == map.end()) {
                map.emplace(p.source, unordered_set<string>());
            }
            map[p.source].emplace(p.dest);
        }
        return map;
    }

    pair<bool, LockDependency> dfs(string from, unordered_map<string, unordered_set<string>> & g, 
                unordered_map<string, string> & visited, int depth) {
        if (g.find(from) == g.end()) {
            return {false, {"", ""}};
        }

        for(const auto & n: g[from]) {
            if (visited.find(n) != visited.end()) {
                return {true, {from, n}};
            }
            visited.emplace(n, from);
            auto r = dfs(n, g, visited, depth + 1);
            if (r.first) {
                return r;
            }
            visited.erase(n);

        }
        return {false, {"", ""}};;
    }

    void find_cycle(unordered_map<string, unordered_set<string>> & g) {

        for (const auto & [k, v]: g) {
            unordered_map<string, string> visited;
            auto r = dfs(k, g, visited, 0);
            if (r.first) {
                cout << "found deadlock(cycle in graph): (" << r.second.source << "->" << r.second.dest << ")" << endl;
                string c = r.second.source;
                while(c.compare(r.second.dest)) {
                    cout << c << "<-";
                    c = visited[c];
                }
                cout << c << "<-" << r.second.source << endl;
                break;
            }
        }
    }

    void test_dfs(const vector<LockDependency> & v) {
        unordered_map<string, unordered_set<string>> g = build_graph(v);
        find_cycle(g);
    }
}

void test_p18_04_deadlock_detection() {
    PRINT_FUNC_NAME;
    vector<p18_04::LockDependency> v{
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
    p18_04::test_dfs(v);
}