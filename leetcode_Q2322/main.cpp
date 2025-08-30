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

    static int dfs_naive(const vector<vector<int>>& graph, const vector<int>& nums, int node, int from) {
        int cur_xor = nums[node];
        for (auto&& next : graph[node]) {
            if (next != from) {
                cur_xor ^= dfs_naive(graph, nums, next, node);
            }
        }
        return cur_xor;
    }
    static int get_diff1(int v1, int v2, int v3) {
        return max(max(v1, v2), v3) - min(min(v1, v2), v3);
    }
    static int naive(vector<int>& nums, vector<vector<int>>& edges) {
        const auto n = size(nums);
        int min_value = INT_MAX;
        for (int i = 0; i < size(edges); i++) {
            for (int j = i + 1; j < size(edges); j++) {
                vector<vector<int>> graph(n);
                union_find uf(n);
                for (int k = 0; k < size(edges); k++) {
                    if (k == i || k == j) {
                        continue;
                    }
                    const auto& edge = edges[k];
                    graph[edge.front()].emplace_back(edge.back());
                    graph[edge.back()].emplace_back(edge.front());
                    uf.unite(edge.front(), edge.back());
                }

                vector<int> xors;
                for (int k = 0; k < n; k++) {
                    if (uf.is_root(k)) {
                        xors.emplace_back(dfs_naive(graph, nums, k, -1));
                    }
                }
                const auto cur_val = get_diff1(xors[0], xors[1], xors[2]);
                min_value = min(min_value, cur_val);
            }
        }
        return min_value;
    }



    static void dfs(const vector<vector<int>>& graph, const vector<int>& nums, int node, int from, vector<int>& dp) {
        int cur_xor = nums[node];
        for (auto&& next : graph[node]) {
            if (next != from) {
                dfs(graph, nums, next, node, dp);
                cur_xor ^= dp[next];
            }
        }
        dp[node] = cur_xor;
    }

    static int get_diff(int v1, int v2, int v3) {
        return max(max(v1, v2), v3) - min(min(v1, v2), v3);
    }

    static int dfs_calc1(const vector<vector<int>>& graph, const vector<int>& nums, int node, int from, int ignore_node, int total_xors, int& min_value, function<int(int, int)> get_value) {
        int cur_part_xor = nums[node];
        for (int i = 0; i < size(graph[node]); i++) {
            const auto& next = graph[node][i];
            if (next != from && next != ignore_node) {
                const auto child_nodes_xor = dfs_calc1(graph, nums, next, node, ignore_node, total_xors, min_value, get_value);
                cur_part_xor ^= child_nodes_xor;
                const auto split = total_xors ^ child_nodes_xor;
                min_value = min(min_value, get_value(split, child_nodes_xor));
            }
        }
        return cur_part_xor;
    }


    static int dfs_calc(const vector<vector<int>>& graph, const vector<int>& nums,int node, int from,int total_xors, int& min_value) {
        int cur_part_xor = nums[node];
        for (int i = 0; i < size(graph[node]); i++) {
            const auto& next = graph[node][i];
            if (next != from) {
                const auto child_nodes_xor = dfs_calc(graph, nums, next, node, total_xors, min_value);
                cur_part_xor ^= child_nodes_xor;
                const auto split = total_xors ^ child_nodes_xor;

                dfs_calc1(graph, nums, 0, -1, next, split, min_value,
                    [&](int a, int b)->int { return get_diff(child_nodes_xor, a, b);  });
            }
        }
        return cur_part_xor;
    }

    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        const auto n = size(nums);
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge.front()].emplace_back(edge.back());
            graph[edge.back()].emplace_back(edge.front());
        }
        const auto total_xors = accumulate(cbegin(nums), cend(nums), 0, [](int a, int b) { return a ^ b; });
        int min_value = INT_MAX;
        dfs_calc(graph, nums, 0, -1, total_xors, min_value);
        return min_value;
    }

};

static void test(vector<int>&& nums, vector<vector<int>>&& edges) {
    cout << Solution().minimumScore(nums, edges) << endl;
    cout << Solution().naive(nums, edges) << endl;
}

int main() {
    //test(get_list_int("[29,11,17,14,16,16,3,27,18,16,13,19,28,8,23,32,25,13,17]"), get_matrix_int("[[17,1],[8,1],[17,2],[8,3],[15,2],[3,4],[8,14],[0,17],[18,2],[3,5],[11,5],[14,10],[18,6],[4,13],[7,6],[16,3],[9,4],[12,11]]"));
    //test(get_list_int("[9,14,2,1]"), get_matrix_int("[[2,3],[3,0],[3,1]]"));
    //test(get_list_int("[19,12,1,27,12]"), get_matrix_int("[[2,3],[4,2],[1,3],[0,3]]"));
    //test(get_list_int("[5,5,2,4,4,2]"), get_matrix_int("[[0,1],[1,2],[5,2],[4,3],[1,3]]"));
    test(get_list_int("[1,5,5,4,11]"), get_matrix_int("[[0,1],[1,2],[1,3],[3,4]]"));
    //test(get_list_int("[1,2,4]"), get_matrix_int("[[0,1],[0,2]]"));
    return 0;
}