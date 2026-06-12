#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
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
    static void tarjan_dfs(
            const vector<vector<size_t>>& graph, 
            const vector<vector<pair<size_t, size_t>>>& queries, 
            size_t node, 
            size_t from, 
            union_find& uf, 
            size_t distance, 
            vector<size_t>& ancestor, 
            vector<size_t>& distances,
            vector<bool>& visited,
            vector<size_t>& lcas) {
        ancestor[node] = node;
        distances[node] = distance;
        for (auto&& child : graph[node]) {
            if (child != from) {
                tarjan_dfs(graph, queries, child, node, uf, distance + 1, ancestor, distances, visited, lcas);
                uf.unite(node, child);
                ancestor[uf.root(node)] = node;
            }
        }
        visited[node] = true;
        for (auto&& [v, query_index] :  queries[node]) {
            if (visited[v]) {
                lcas[query_index] = ancestor[uf.root(v)];
            }
        }
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        constexpr long long MODULO = 1e9 + 7;
        const auto nodes = size(edges) + 1;
        vector<vector<size_t>> graph(nodes);
        for (auto&& edge : edges) {
            const auto u = edge.front() - 1;
            const auto v = edge.back() - 1;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<vector<pair<size_t, size_t>>> queries2(nodes);
        vector<size_t> lcas(size(queries));
        for (size_t i = 0; i < size(queries); i++) {
            const auto& q = queries[i];
            const size_t u = q.front() - 1;
            const size_t v = q.back() - 1;
            queries2[u].push_back({ v, i });
            queries2[v].push_back({ u, i });
        }
        union_find uf(nodes);
        vector<size_t> ancestors(nodes);
        vector<size_t> distances(nodes);
        vector<bool> visited(nodes);
        tarjan_dfs(graph, queries2, 0, nodes + 1, uf, 0, ancestors, distances, visited, lcas);

        vector<long long> p2(nodes * 2 + 1);
        p2[0] = 1;
        for (long long i = 1; i < nodes * 2 + 1; i++) {
            p2[i] = (2 * p2[i - 1]) % MODULO;
        }

        vector<int> ans;
        ans.reserve(size(queries));

        for (size_t i = 0; i < size(queries); i++) {
            const auto& q = queries[i];
            const size_t u = q.front() - 1;
            const size_t v = q.back() - 1;
            const auto distance = distances[u] + distances[v] - 2 * distances[lcas[i]];
            if (distance == 0) {
                ans.push_back(0);
            }
            else {
                ans.push_back(p2[distance - 1]);
            }
        }



        return ans;
    }
};

static void test(vector<vector<int>>&& edges, vector<vector<int>>&& queries) {
    output(Solution().assignEdgeWeights(edges, queries));
}

int main() {
    test(get_matrix_int("[[1,2],[2,3],[3,4],[4,5]]"), get_matrix_int("[[1,5],[2,5],[3,5],[4,5],[5,5]]"));
    test(get_matrix_int("[[1,2]]"), get_matrix_int("[[1,1],[1,2]]"));
    test(get_matrix_int("[[1,2],[1,3],[3,4],[3,5]]"), get_matrix_int("[[1,4],[3,4],[2,5]]"));

    return 0;
}
