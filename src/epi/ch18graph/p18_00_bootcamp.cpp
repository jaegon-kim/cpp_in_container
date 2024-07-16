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

    void dump_indent(int depth) {
        //cout << " ";
        for (int i = 0; i < depth; i++) {
            cout << "   ";
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
        unordered_set<string> & visited, int depth) {
        
        cout << "->" << from;

        if (g.find(from) == g.end()) {
            cout << "." << endl; dump_indent(depth);
            return list<Game>();
        }
        unordered_set<string> nexts = g[from];
        if (nexts.find(to) != nexts.end()) {
            list<Game> l;
            l.push_front(Game{from, to});
            cout << "->" << to << endl;
            return l;
        }

        for(const auto & n: nexts) {

            if (visited.find(n) != visited.end()) {
                continue;
            }

            visited.emplace(n);
            auto r = dfs_search(n, to, g, visited, depth + 1);
            visited.erase(n);

            if (r.size()) {
                r.push_front(Game{from, n});
                return r;
            }
        }
        cout << "." <<endl; dump_indent(depth);
        return list<Game>();
    }

    void test_dfs(const vector<Game> & v, string from, string to) {
        unordered_map<string, unordered_set<string>> g = build_graph(v);
        unordered_set<string> visited;
        cout << "<dfs(depth first search)>" << endl;
        //dump_graph(g, true);
        auto r = dfs_search(from, to, g, visited, 0);
        cout << "found path: ";
        dump_list(r, true);
    }

    list<Game> bfs_search(string from, string to, unordered_map<string, unordered_set<string>> & g) {

        unordered_map<string, string> prev;
        list<string> q;
        q.push_back(from);
        prev.emplace(from, from);

        list<Game> path;

        while(q.size()) {
            string n = q.front();
            q.pop_front();
            for (const auto & e: g[n]) {
                if (prev.find(e) != prev.end()) {
                    continue;
                }
                prev.emplace(e, n);
                if (!to.compare(e)) {
                    //cout << "found" << endl;
                    //dump_map(prev, true);
                    string c = to;
                    while(c.compare(from)) {
                        string p = prev[c];
                        path.push_front(Game{p, c});
                        c = p;
                    }
                    return path;
                }
                q.push_back(e);
            }
        }

        return path;
    }

    void test_bfs(const vector<Game> & v, string from, string to) {
        unordered_map<string, unordered_set<string>> g = build_graph(v);
        unordered_set<string> visited;
        cout << "<bfs(breadth first search)>" << endl;
        //dump_graph(g, true);
        auto r = bfs_search(from, to, g);
        cout << "found path: ";
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

    //p18_00::test_dfs(v, "a", "h");
    //p18_00::test_dfs(v, "a", "g");
 
    p18_00::test_dfs(v, "a", "l");
    p18_00::test_bfs(v, "a", "l");

    //p18_00::test_dfs(v, "l", "h");
    //p18_00::test_dfs(v, "a", "a");
    //p18_00::test_dfs(v, "h", "a");

}