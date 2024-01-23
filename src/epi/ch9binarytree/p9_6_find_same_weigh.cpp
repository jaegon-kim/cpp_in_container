#include <iostream>
#include <vector>
#include <unordered_map>
#include "binary_tree.hpp"
#include "utility/dump.hpp"

using namespace std;

namespace p9_6 {

    using node_ptr = shared_ptr<Node<int>>;

    node_ptr N(int v) {
        node_ptr new_node = make_shared<Node<int>>(v);
        return new_node;
    }

    node_ptr N(int v, node_ptr left, node_ptr right) {
        node_ptr new_node = make_shared<Node<int>>(v);
        new_node->left = left;
        new_node->right = right;
        return new_node;
    }

    void traverse(node_ptr node, node_ptr target, unsigned long long & target_weight,
                    unsigned long long weight, 
                    vector<unsigned long long> & path,
                    unordered_map<unsigned long long, shared_ptr<vector<vector<unsigned long long>>>> & map) {
        if (!node) {
            return;
        }
        weight += node->data;
        path.push_back(node->data);

        if (map.find(weight) == map.end()) {
            map[weight] = make_shared<vector<vector<unsigned long long>>>();
        }
        map[weight]->emplace_back(path);

        if (node == target) {
            target_weight = weight;
        }

        if (!node->left && !node->right) {
            dump_vec<unsigned long long>(path, false);
            cout << " " << weight << endl;
        } else {
            traverse(node->left, target, target_weight, weight, path, map);
            traverse(node->right, target, target_weight, weight, path, map);
        }
        path.pop_back();
        return;
    }

    void dump_vec_path(shared_ptr<vector<vector<unsigned long long>>> & ptr_vec_path) {
        size_t len = ptr_vec_path->size();
        for (size_t i = 0; i < len; i++) {
            vector<unsigned long long> path = ptr_vec_path->at(i);
            cout << " " ;
            dump_vec<unsigned long long>(path, true);
        }
    }

    void dump_map(unordered_map<unsigned long long, shared_ptr<vector<vector<unsigned long long>>>> & map) {
        for (auto e: map) {
            cout << e.first << endl;
            dump_vec_path(e.second);
        }
    }

    void test() {

        vector<unsigned long long> path;
        unordered_map<unsigned long long, shared_ptr<vector<vector<unsigned long long>>>> map;
        unsigned long long target_weight = 0;

        node_ptr node_e = N(0);
        node_ptr root = 
            N(314, N(6, N(271, N(28), node_e), N(561, nullptr , N(3, nullptr, N(7)))), 
                N(6, N(2, N(1, N(401, nullptr, N(641)), N(257)), nullptr), N(274, nullptr, N(28))));
        traverse(root, node_e, target_weight, 0, path, map);
        dump_map(map);

        cout << "target weight: " << target_weight << endl;
        if (target_weight) {
            dump_vec_path(map[target_weight]);
        }
    }
}

void test_p9_6_find_same_weigh() {
    PRINT_FUNC_NAME;
    p9_6::test();
}