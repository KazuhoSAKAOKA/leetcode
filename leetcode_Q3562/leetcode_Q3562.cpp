#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    static int WA(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        if (n == 1) {
            return budget >= present[0] ? max(future[0] - present[0], 0) : 0;
        }
        vector<vector<int>> graph(n);
        for (auto&& edge : hierarchy) {
            const auto u = edge.front() - 1;
            const auto v = edge.back() - 1;
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(budget + 1, INT_MIN / 2)));
        dp[0][0][0] = 0;
        if (present[0] <= budget) {
            dp[0][1][present[0]] = future[0] - present[0];
        }
        vector<bool> visited(n);
        visited[0] = true;
        queue<pair<int, int>> q;
        for (auto&& next : graph[0]) {
            q.push({ 0, next });
            visited[next] = true;
        }
        vector<int> leaves;
        while (!q.empty()) {
            const auto [boss, current] = q.front();
            q.pop();
            dp[current][0][0] = 0;
            const int normal_profit = future[current] - present[current];
            const int discount_cost = present[current] / 2;
            const int discount_profit = future[current] - discount_cost;
            for (int i = 0; i < budget; i++) {
                dp[current][0][i] = max(dp[boss][0][i], dp[boss][1][i]);
                if (i + present[current] <= budget) {
                    dp[current][1][i + present[current]] = max(dp[current][1][i + present[current]], dp[boss][0][i] + normal_profit);
                }
                if (i + discount_cost <= budget) {
                    dp[current][1][i + discount_cost] = max(dp[current][1][i + discount_cost], dp[boss][1][i] + discount_profit);
                }
            }
            bool exist = false;
            for (auto&& next : graph[current]) {
                if (next != boss) {
                    exist = true;
                    visited[next] = true;
                    q.push({ current, next });
                }
            }
            if (!exist) {
                leaves.emplace_back(current);
            }
        }

        vector<vector<int>> dp1(size(leaves), vector<int>(budget + 1));
        for (int j = 0; j <= budget; j++) {
            dp1[0][j] = max(dp[leaves[0]][0][j], dp[leaves[0]][1][j]);
        }
        for (int i = 1; i < size(leaves); i++) {
            for (int j = 0; j <= budget; j++) {
                dp1[i][j] = max(dp[leaves[i]][0][j], dp[leaves[i]][1][j]);
            }
            for (int j = 1; j <= budget; j++) {
                int max_value = 0;
                for (int k = 0; k <= j; k++) {
                    for (int l = 0; k + l <= j; l++) {
                        max_value = max(max_value, dp1[i][k] + dp1[i - 1][l]);
                    }
                }
                dp1[i][j] = max(dp1[i][j], max_value);
            }
        }
        int profit = 0;

        for (int i = 0; i <= budget; i++) {
            profit = max(profit, dp1.back()[i]);
        }
        return profit;
    }

    static void dfs(int budget, const vector<vector<int>>& graph, const vector<int>& present, const vector<int>& future, int current, vector<vector<vector<int>>>& dp) {
        for (auto&& child : graph[current]) {
            dfs(budget, graph, present, future, child, dp);
            for (int i = 0; i <= budget; i++) {
                dp[current][0][i - present[current]] = max(dp[current][0][i - present[current]], dp[current][0][i] + normal_gain);
            }
            for (int i = 0; i <= budget; i++) {
                dp[current][1][i - discount] = max(dp[current][1][i - discount], dp[current][1][i] + discount_gain);
            }

        }

        const int discount = present[current] / 2;
        const int normal_gain = future[current] - present[current];
        const int discount_gain = future[current] - discount;
        for (int i = present[current]; i <= budget; i++) {
            dp[current][0][i - present[current]] = max(dp[current][0][i - present[current]], dp[current][0][i] + normal_gain);
        }
        for (int i = discount; i <= budget; i++) {
            dp[current][1][i - discount] = max(dp[current][1][i - discount], dp[current][1][i] + discount_gain);
        }
    }

    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        if (n == 1) {
            return budget >= present[0] ? max(future[0] - present[0], 0) : 0;
        }
        vector<vector<int>> graph(n);
        for (auto&& edge : hierarchy) {
            const auto u = edge.front() - 1;
            const auto v = edge.back() - 1;
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(budget + 1, vector<int>(2, -1)));
        dp[0][budget][0] = 0;
        if (present[0] <= budget) {
            dp[0][1][present[0]] = future[0] - present[0];
        }
        vector<bool> visited(n);
        visited[0] = true;
        queue<pair<int, int>> q;
        for (auto&& next : graph[0]) {
            q.push({ 0, next });
            visited[next] = true;
        }
        vector<int> leaves;
        while (!q.empty()) {
            const auto [boss, current] = q.front();
            q.pop();
            dp[current][0][0] = 0;
            const int normal_profit = future[current] - present[current];
            const int discount_cost = present[current] / 2;
            const int discount_profit = future[current] - discount_cost;
            for (int i = 0; i < budget; i++) {
                dp[current][0][i] = max(dp[boss][0][i], dp[boss][1][i]);
                if (i + present[current] <= budget) {
                    dp[current][1][i + present[current]] = max(dp[current][1][i + present[current]], dp[boss][0][i] + normal_profit);
                }
                if (i + discount_cost <= budget) {
                    dp[current][1][i + discount_cost] = max(dp[current][1][i + discount_cost], dp[boss][1][i] + discount_profit);
                }
            }
            bool exist = false;
            for (auto&& next : graph[current]) {
                if (next != boss) {
                    exist = true;
                    visited[next] = true;
                    q.push({ current, next });
                }
            }
            if (!exist) {
                leaves.emplace_back(current);
            }
        }

        vector<vector<int>> dp1(size(leaves), vector<int>(budget + 1));
        for (int j = 0; j <= budget; j++) {
            dp1[0][j] = max(dp[leaves[0]][0][j], dp[leaves[0]][1][j]);
        }
        for (int i = 1; i < size(leaves); i++) {
            for (int j = 0; j <= budget; j++) {
                dp1[i][j] = max(dp[leaves[i]][0][j], dp[leaves[i]][1][j]);
            }
            for (int j = 1; j <= budget; j++) {
                int max_value = 0;
                for (int k = 0; k <= j; k++) {
                    for (int l = 0; k + l <= j; l++) {
                        max_value = max(max_value, dp1[i][k] + dp1[i - 1][l]);
                    }
                }
                dp1[i][j] = max(dp1[i][j], max_value);
            }
        }
        int profit = 0;

        for (int i = 0; i <= budget; i++) {
            profit = max(profit, dp1.back()[i]);
        }
        return profit;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
