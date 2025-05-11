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
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    int minDeletion(string s, int k) {
        vector<int> freqs(26);
        for (auto&& c : s) {
            freqs[c - 'a']++;
        }
        sort(begin(freqs), end(freqs), greater<int>());
        int count = 0;
        for (int i = k; i < 26; i++) {
            count += freqs[i];
        }
        return count;
    }
};
void test(string&& s, int k) {
    cout << Solution().minDeletion(s, k) << endl;
}
static void run() {
    test("abc", 2);
    test("aabb", 2);
    test("yyyzz", 1);
}
}
namespace problem2 {
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        const auto m = size(grid);
        const auto n = size(grid.front());
        vector<vector<long long>> prefix_sums(m + 1, vector<long long>(n + 1, 0LL));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + static_cast<long long>(grid[i][j]);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }

        auto get_sum = [&](int ybegin, int xbegin, int yend, int xend) -> long long {
            return prefix_sums[yend][xend] - prefix_sums[yend][xbegin] - prefix_sums[ybegin][xend] + prefix_sums[ybegin][xbegin];
            };
        const auto total = prefix_sums[m][n];
        if (total % 2 != 0) {
            return false;
        }
        const auto half = total / 2;

        for (int i = 1; i < m; i++) {
            if (get_sum(0, 0, i, n) == half) {
                return true;
            }
        }
        for (int i = 1; i < n; i++) {
            if (get_sum(0, 0, m, i) == half) {
                return true;
            }
        }
        return false;
    }
};
static void test(vector<vector<int>>&& grid) {
    cout << Solution().canPartitionGrid(grid) << endl;
}
static void run() {
    test(get_matrix_int("[[1,4],[2,3]]"));
    test(get_matrix_int("[[1,3],[2,4]]"));
}

}
namespace problem3 {
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

    static int get_center(const vector<vector<int>>& graph, int current, int from, int remain) {
        if (remain == 0) {
            return current;
        }
        for (auto&& next : graph[current]) {
            if (next != from) {
                return get_center(graph, next, current, remain - 1);
            }
        }
        throw exception();
    }

    static int find_center(const vector<vector<int>>& graph, int current, int from, int nodes) {
        if (size(graph[current]) == 1) {
            return get_center(graph, graph[current][0], current, (nodes / 2) - 1);
        }
        for (auto&& next : graph[current]) {
            if (next != from) {
                return find_center(graph, next, current, nodes);
            }
        }
        throw exception();
    }

    long long maxScore(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        union_find uf(n);
        for (auto&& edge : edges) {
            const auto u = edge.front();
            const auto v = edge.back();
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
            uf.unite(u, v);
        }
        map<int, int> edge_count_map;
        vector<int> single_nodes;
        vector<int> pair_nodes;
        vector<int> more_nodes;
        for (int i = 0; i < n; i++) {
            if (uf.is_root(i)) {
                const auto connect_size = uf.size(i);
                if (connect_size == 1) {
                    single_nodes.emplace_back(i);
                }
                else if(connect_size == 2){
                    pair_nodes.emplace_back(i);
                }
                else {
                    more_nodes.emplace_back(i);
                }
            }
            edge_count_map[uf.root(i)] += size(graph[i]);
        }
        map<int, vector<int>, greater<int>> line_nodes;
        map<int, vector<int>> loop_nodes;
        for (auto&& root : more_nodes) {
            if (edge_count_map[root] / 2 == uf.size(root)) {
                loop_nodes[uf.size(root)].emplace_back(root);
            }
            else {
                line_nodes[uf.size(root)].emplace_back(root);
            }
        }
        vector<long long> node_value(n, 0);
        vector<bool> visited(n);
        int current_node_value = n;
        for (auto&& [_, connecteds] : loop_nodes) {
            for (auto&& root : connecteds) {
                queue<int> q;
                q.push(root);
                node_value[root] = current_node_value;
                current_node_value--;
                while (!q.empty()) {
                    const auto cur = q.front();
                    q.pop();
                    for (auto&& next : graph[cur]) {
                        if (node_value[next] == 0) {
                            node_value[next] = current_node_value;
                            current_node_value--;
                            q.push(next);
                        }
                    }
                }
            }
        }

        for (auto&& [_, connecteds] : line_nodes) {
            for (auto&& root : connecteds) {
                queue<int> q;
                const auto center = find_center(graph, root, -1, uf.size(root));
                q.push(center);
                node_value[center] = current_node_value;
                current_node_value--;
                while (!q.empty()) {
                    const auto cur = q.front();
                    q.pop();
                    vector<int> nexts(cbegin(graph[cur]), cend(graph[cur]));
                    sort(begin(nexts), end(nexts), [&](const auto& a, const auto& b) { return size(graph[a]) > size(graph[b]); });
                    for (auto&& next : nexts) {
                        if (node_value[next] == 0) {
                            node_value[next] = current_node_value;
                            current_node_value--;
                            q.push(next);
                        }
                    }
                }
            }
        }

        for (auto&& p : pair_nodes) {
            node_value[p] = current_node_value;
            current_node_value--;
            node_value[graph[p][0]] = current_node_value;
            current_node_value--;
        }
        long long ans = 0LL;
        for (auto&& edge : edges) {
            ans += node_value[edge.front()] * node_value[edge.back()];
        }

        //for (auto&& p : single_nodes) {
        //    ans += current_node_value;
        //    current_node_value--;
        //}
        return ans;
    }
}; 
static void test(int n, vector<vector<int>>&& edges) {
    cout << Solution().maxScore(n, edges) << endl;
}
static void run() {
    test(7, get_matrix_int("[[0,1],[1,2],[2,0],[3,4],[4,5],[5,6]]"));
    test(6, get_matrix_int("[[0,3],[4,5],[2,0],[1,3],[2,4],[1,5]]"));
}
}
namespace problem4 {
static void run() {
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    problem3::run();
    problem4::run();
    return 0;
}