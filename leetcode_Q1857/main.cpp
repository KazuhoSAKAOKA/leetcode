#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <queue>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    using graph_t = vector<vector<int>>;
    static vector<int> topo_sort(const graph_t& G) {  // bfs
        vector<int> ans;
        int n = (int)G.size();
        vector<int> ind(n);            // ind[i]: 頂点iに入る辺の数(次数)
        for (int i = 0; i < n; i++) {  // 次数を数えておく
            for (auto e : G[i]) {
                ind[e]++;
            }
        }
        queue<int> que;
        for (int i = 0; i < n; i++) {  // 次数が0の点をキューに入れる
            if (ind[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {  // 幅優先探索
            int now = que.front();
            ans.push_back(now);
            que.pop();
            for (auto e : G[now]) {
                ind[e]--;
                if (ind[e] == 0) {
                    que.push(e);
                }
            }
        }
        return ans;
    }

    int largestPathValue(string colors, vector<vector<int>>& edges) {
        const auto n = size(colors);
        vector<vector<int>> graph(n);
        map<int, int> incounts;
        for (auto&& edge : edges) {
            graph[edge.front()].emplace_back(edge.back());
        }
        const auto top_res = topo_sort(graph);
        if (n != size(top_res)) {
            return -1;
        }

        vector<vector<int>> dp(n, vector<int>(26));

        for (auto&& node : top_res) {
            dp[node][colors[node] - 'a']++;
            for (auto&& next : graph[node]) {
                for (int i = 0; i < 26; i++) {
                    dp[next][i] = max(dp[next][i], dp[node][i]);
                }
            }
        }

        int max_colors = 0;
        for (int i = 0; i < n; i++) {
            max_colors = max(max_colors, *max_element(cbegin(dp[i]), cend(dp[i])));
        }

        return max_colors;
    }
};

void test(string&& colors, vector<vector<int>>&& edges) {
    cout << Solution().largestPathValue(colors, edges) << endl;
}
int main() {
    test("ab", get_matrix_int("[[0,1],[1,1]]"));

    test("aaaa", get_matrix_int("[[0,1],[0,2],[1,3],[2,3]"));
    test("hhqhuqhqff", get_matrix_int("[[0,1],[0,2],[2,3],[3,4],[3,5],[5,6],[2,7],[6,7],[7,8],[3,8],[5,8],[8,9],[3,9],[6,9]]"));
    test("abaca", get_matrix_int("[[0,1],[0,2],[2,3],[3,4]]"));
    test("a", get_matrix_int("[[0,0]]"));
    return 0;
}