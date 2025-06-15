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

    static long long get_min_cost(int n, int k) {
        if (n <= k) { return 0; }
        long long min_cost = LLONG_MAX;
        for (int i = n - k; i <= k; i++) {
            min_cost = min(min_cost, static_cast<long long>(i) * static_cast<long long>(n - i));
        }
        return min_cost;
    }
    long long minCuttingCost(int n, int m, int k) {
        long long cost = 0;

        cost += get_min_cost(n, k);
        cost += get_min_cost(m, k);

        return cost;
    }
};
static void test(int n, int m, int k) {
    cout << Solution().minCuttingCost(n, m, k) << endl;
}
static void run() {
    test(6, 5, 5);
    test(4, 4, 6);
}
}
namespace problem2 {
class Solution {
public:

    static bool removal(char a, char b) {
        const auto diff = abs(a - b);
        return diff == 1 || diff == 25;
    }

    string resultingString(string s) {
        char before = s[0];
        string ans;
        ans.reserve(size(s));

        int i = 1;
        while(i < size(s)) {
            if (removal(before, s[i])) {
                if (ans.empty()) {
                    i++;
                    if (i == size(s)) {
                        before = 0;
                        break;
                    }
                    before = s[i];
                }
                else {
                    before = ans.back();
                    ans.pop_back();
                }
            }
            else {
                ans += before;
                before = s[i];
            }
            i++;
        }
        if (before != 0) {
            ans += before;
        }
        return ans;
    }
};
void test(string&& s) {
    cout << Solution().resultingString(s) << endl;
}
static void run() {
    test("zadb");
    test("abc");
    test("llgjfilkhgiil");
    test("adcb");
}
}
namespace problem3 {
class Solution {
public:
    /*
    static int rec(const vector<vector<int>>& graph, const vector<int>& present, const vector<int>& future, int boss, int current, int& remain_budget, vector<vector<vector<int>>>& dp) {


        dp[current][0][0] = 0;
        const int normal_profit = future[current] - present[current];
        const int discount_cost = present[current] / 2;
        const int discount_profit = future[current] - discount_cost;
        for (int i = 0; i < remain_budget; i++) {
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
    */

    static int rec_boss(int n, int present, int future, int budget, const vector<int>& juniors, int current, int index, int cur_use, int cur_profit, int cur_discount_tag) {
        if (size(juniors) == index) {
            return ;
        }
        const auto junior = juniors[index];
        rec_boss(n, present, future, budget, juniors, current, index + 1, memo, cur_use, cur_profit, cur_discount_tag);
        for (auto&& [used, profit] : memo[junior][cur_discount_tag]) {
            if (used + cur_use <= present) {
                rec_boss(n, present, future, budget, juniors, current, index + 1, memo, cur_use + used, cur_profit + profit, cur_discount_tag);
            }
        }
    }

    static void rec(int n, const vector<vector<int>>& graph, const vector<int>& present, const vector<int>& future, int budget, int current, int boss, vector<vector<unordered_map<int, int>>>& memo) {
        vector<int> juniors;
        for (auto&& node : graph[current]) {
            if (node != boss) {
                juniors.emplace_back(node);
            }
        }
        if (juniors.empty()) {
            memo[current][0][0] = 0;
            memo[current][1][0] = 0;
            if (present[current] <= budget) {
                memo[current][0][present[current]] = future[current] - present[current];
            }
            if (present[current] / 2 <= budget) {
                memo[current][1][present[current] / 2] = future[current] - present[current] / 2;
            }
            return;
        }

        rec_boss(n, present[current], future[current], budget, juniors, current, 0, memo, )
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
};
static void test(int n, vector<int>&& present, vector<int>&& future, vector<vector<int>>&& hierarchy, int budget) {
    cout << Solution().maxProfit(n, present, future, hierarchy, budget) << endl;
}

static void run() {
    test(3, get_list_int("[6,4,23]"), get_list_int("[50,48,17]"), get_matrix_int("[[1,3],[1,2]]"), 65);
    test(2, get_list_int("[21,44]"), get_list_int("[3,13]"), get_matrix_int("[[1,2]]"), 65);
    test(1, get_list_int("[45]"), get_list_int("[38]"), get_matrix_int("[]"), 115);
    test(3, get_list_int("[4,6,8]"), get_list_int("[7,9,11]"), get_matrix_int("[[1,2],[1,3]]"), 10);
    test(2, get_list_int("[1,2]"), get_list_int("[4,3]"), get_matrix_int("[[1,2]]"), 3);
    test(2, get_list_int("[3,4]"), get_list_int("[5,8]"), get_matrix_int("[[1,2]]"), 4);
    test(3, get_list_int("[5,2,3]"), get_list_int("[8,5,6]"), get_matrix_int("[[1,2],[2,3]]"), 7);
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