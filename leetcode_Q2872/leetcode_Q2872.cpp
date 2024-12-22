// leetcode_Q2872.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static int single_route(int n, const vector<set<int>>& graph, vector<int>& fixed_values, vector<bool>& checked, int k, vector<int>& dp, int node) {
        if (checked[node]) { return node; }
        checked[node] = true;
        const auto next = *graph[node].cbegin();
        if (fixed_values[node] % k == 0) {
            dp[next]++;
        }
        else {
            fixed_values[next] += fixed_values[node];
        }
        if (size(graph[next]) == 1) {
            return single_route(n, graph, fixed_values, checked, k, dp, next);
        }
        else {
            return next;
        }
    }

    static int dfs(const vector<set<int>>& graph, int node,int from, const vector<int>& values, int k, int& count) {
        int sum = values[node];

        for (auto&& next : graph[node]) {
            if (next != from) {
                sum += dfs(graph, next, node, values, k, count);
            }
        }
        if (sum % k == 0) { count++; }
        return sum;
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        if (n == 1) { return 1; }
        if (n == 2) { return (values[0] % k == 0) && (values[1] % k == 0) ? 2 : 1; }
        vector<set<int>> graph(n);
        for (auto&& edge : edges) {
            const auto u = edge.front();
            const auto v = edge.back();
            graph[u].insert(v);
            graph[v].insert(u);
        }

        int count = 0;
        dfs(graph, 0, -1, values, k, count);
        return count;
    }
};

void test(int n, vector<vector<int>>&& edges, vector<int>&& values, int k) {
    cout << Solution().maxKDivisibleComponents(n, edges, values, k) << endl;
}
int main()
{
    test(5, get_matrix_int("[[0,2],[1,2],[1,3],[2,4]]"), get_list_int("[1,8,1,4,4]"), 6);
    test(7, get_matrix_int("[[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]"), get_list_int("[3,0,6,1,5,2,1]"), 3);
    return 0;
}