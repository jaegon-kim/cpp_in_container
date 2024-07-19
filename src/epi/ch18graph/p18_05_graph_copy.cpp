#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "utility/dump.hpp"
using namespace std;
namespace p18_05 {

    struct Node {
        Node(string _label) : label(_label) {}
        unordered_set<shared_ptr<Node>> vertex;
        string label;
    };

    void dump_graph(const unordered_map<string, shared_ptr<Node>> & g, bool nl) {
        for (const auto & [key, val]: g) {
            cout << key << "->{";
            for (const auto & e: val->vertex) {
                cout << e->label << ", ";
            }
            cout << "}" << endl;
        }
        if (nl) {
            cout << endl;
        }
    }

    unordered_map<string, shared_ptr<Node>> build_graph(const vector<pair<string, string>> & v) {
        unordered_map<string, shared_ptr<Node>> map;
        for (const auto & [src, dst]: v) {
            if (map.find(src) == map.end()) {
                map.emplace(src, make_shared<Node>(src));
            }

            if (map.find(dst) == map.end()) {
                map.emplace(dst, make_shared<Node>(dst));
            }

            map[src]->vertex.emplace(map[dst]);
        }
        return map;
    }

    void dfs(shared_ptr<Node> o_n, 
        unordered_map<string, shared_ptr<Node>> & o_g, 
            unordered_map<string, shared_ptr<Node>> & n_g,
                unordered_set<string> & visited) {
        
        visited.emplace(o_n->label);

        for (const auto & v: o_n->vertex) {
            if (visited.find(v->label) != visited.end()) {
                n_g[o_n->label]->vertex.emplace(n_g[v->label]);
                continue;
            }
            n_g.emplace(v->label, make_shared<Node>(v->label));
            n_g[o_n->label]->vertex.emplace(n_g[v->label]);

            dfs(v, o_g, n_g, visited);
        }
    }

    unordered_map<string, shared_ptr<Node>>
    copy_graph(unordered_map<string, shared_ptr<Node>> & o_g, string label) {

        unordered_map<string, shared_ptr<Node>> n_g;
        if (o_g.find(label) == o_g.end()) {
            return n_g;
        }

        n_g.emplace(label, make_shared<Node>(label));

        unordered_set<string> visited;
        dfs(o_g[label], o_g, n_g, visited);
        return n_g;
    }

    void test(const vector<pair<string, string>> & v, string label) {
        unordered_map<string, shared_ptr<Node>> o_g = build_graph(v);
        cout << "origin grap:" << endl;
        dump_graph(o_g, true);
        unordered_map<string, shared_ptr<Node>> n_g = copy_graph(o_g, label);
        cout << "copied graph from '" << label << "':" << endl;
        dump_graph(n_g, true);
    }
}

void test_p18_05_graph_copy() {
    PRINT_FUNC_NAME;
    vector<pair<string, string>> v{
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
    p18_05::test(v, "a");
}