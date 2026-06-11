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

    static size_t dfs(const vector<vector<size_t>>& graph, size_t node, size_t from) {
        size_t depth = 0;
        for (auto&& child : graph[node]) {
            if (child != from) {
                depth = max(depth, dfs(graph, child, node) + 1);
            }
        }
        return depth;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {
        constexpr long long MODULO = 1e9 + 7;
        const auto nodes = size(edges) + 1;
        vector<vector<size_t>> graph(nodes);
        for (auto&& edge : edges) {
            const auto u = edge.front() - 1;
            const auto v = edge.back() - 1;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        const auto n1 = dfs(graph, 0, nodes + 1);
        const auto max_comb = n1 + 2;
        vector<long long> fac(max_comb);
        vector<long long> finv(max_comb);
        vector<long long> inv(max_comb);
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (long long i = 2; i < max_comb; i++) {
            fac[i] = fac[i - 1] * i % MODULO;
            inv[i] = MODULO - inv[MODULO % i] * (MODULO / i) % MODULO;
            finv[i] = finv[i - 1] * inv[i] % MODULO;
        }
        auto get_comb = [&](int n, int k)-> long long {
            if (n < k) return 0;
            if (n < 0 || k < 0) return 0;
            return fac[n] * (finv[k] * finv[n - k] % MODULO) % MODULO;
            };
        long long ans = 0;

        for (long long i = 1; i <= n1; i += 2) {
            ans += get_comb(n1, i);
            ans %= MODULO;
        }

        return static_cast<int>(ans);
    }
};

static void test(vector<vector<int>>&& edges) {
    cout << Solution().assignEdgeWeights(edges) << endl;
}
int main() {
    test(get_matrix_int("[[1,2]]"));
    test(get_matrix_int("[[1,2],[1,3],[3,4],[3,5]]"));

    return 0;
}
