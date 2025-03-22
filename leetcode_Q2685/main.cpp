#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    struct union_find {

        std::vector<size_t> parents_;
        std::vector<size_t> sizes_;

        union_find(size_t n) : parents_(n, 0), sizes_(n, 1) {
            for (size_t i = 0; i < n; i++) {
                parents_[i] = i;
            }
        }

        size_t root(size_t x) {
            if (x == parents_[x]) { return x; }
            parents_[x] = root(parents_[x]);
            return parents_[x];
        }

        bool same(size_t x, size_t y) {
            return root(x) == root(y);
        }

        void unite(size_t x, size_t y) {
            const auto rootx = root(x);
            const auto rooty = root(y);
            if (rootx == rooty) { return; }
            if (sizes_[rootx] < sizes_[rooty]) {
                parents_[rootx] = rooty;
                sizes_[rooty] += sizes_[rootx];
            }
            else {
                parents_[rooty] = rootx;
                sizes_[rootx] += sizes_[rooty];
            }
        }

        size_t size(size_t x) {
            return sizes_[root(x)];
        }

        bool is_root(size_t x) {
            return root(x) == x;
        }
    };


    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        union_find uf(n);
        vector<set<int>> graph(n);
        for (auto&& edge : edges) {
            const auto u = edge.front();
            const auto v = edge.back();
            uf.unite(u, v);
            graph[u].insert(v);
            graph[v].insert(u);
        }
        map<int, vector<int>> nodes;
        for (int i = 0; i < n; i++) {
            nodes[uf.root(i)].emplace_back(i);
        }
        int count = 0;
        for (auto&& [_, subgraph_nodes] : nodes) {
            const auto subgraph_size = size(subgraph_nodes);
            if (all_of(cbegin(subgraph_nodes), cend(subgraph_nodes), [&](int node) { return size(graph[node]) == subgraph_size - 1; })) {
                count++;
            }
        }
        return count;
    }
};

void test(int n, vector<vector<int>>&& edges) {
    cout << Solution().countCompleteComponents(n, edges) << endl;
}

int main() {
    test(6, get_matrix_int("[[0,1],[0,2],[1,2],[3,4]]"));
    test(6, get_matrix_int("[[0,1],[0,2],[1,2],[3,4],[3,5]]"));
    return 0;
}