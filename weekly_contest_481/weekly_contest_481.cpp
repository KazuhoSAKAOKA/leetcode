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
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

namespace problem1 {
class Solution {
public:
    long long reverse(long long n) {
        if (n == 0) { return 0; }
        vector<int> digits;
        while (n > 0) {
            digits.emplace_back(n % 10);
            n /= 10;
        }
        int value = 0;
        long long base = 1;
        for (auto it = crbegin(digits); it != crend(digits); ++it) {
            value += *it * base;
            base *= 10;
        }

        return value;
    }
    int mirrorDistance(int n) {
        const auto rev = reverse(n);
        return static_cast<int>(abs(n - rev));
    }
};
static void test(int n) {
    cout << Solution().mirrorDistance(n) << endl;
}
static void run() {
    test(25);
    test(10);
    test(7);
}
}

namespace problem2 {
class Solution {
public:
    long long minCost(string s, vector<int>& cost) {
        const auto n = size(s);
        vector<long long> costs(26);
        for (int i = 0; i < n; i++) {
            const auto index = s[i] - 'a';
            for (int j = 0; j < 26; j++) {
                if (j == index) {
                        
                }
                else {
                    costs[j] += static_cast<long long>(cost[i]);
                }
            }
        }
        long long min_cost = LLONG_MAX;
        for (int j = 0; j < 26; j++) {
            min_cost = min(min_cost, costs[j]);
        }
        return min_cost;
    }
};
static void test(string&& s, vector<int>&& cost) {
    cout << Solution().minCost(s, cost) << endl;
}
static void run() {
    test("aabaac", get_list_int("[1,2,3,4,1,10]"));
    test("abc", get_list_int("[10,5,8]"));
    test("zzzzz", get_list_int("[67,67,67,67,67]"));
}
}

namespace problem3 {
class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        return 0;
    }
};
static void test(vector<int>&& nums, vector<int>&& forbidden) {
    cout << Solution().minSwaps(nums, forbidden) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"), get_list_int("[3,2,1]"));
    test(get_list_int("[4,6,6,5]"), get_list_int("[4,6,5,5]"));
    test(get_list_int("[7,7]"), get_list_int("[8,7]"));
    test(get_list_int("[1,2]"), get_list_int("[2,1]"));
}
}

namespace problem4 {
class Solution {
public:

    static void warshall_floyd(std::vector<std::vector<long long>>& dist) {
        const auto V = size(dist);
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    static long long tle(int n, vector<vector<int>>& edges, vector<int>& group) {
        constexpr long long INF = 1e17;
        vector<std::vector<long long>> dist(n, std::vector<long long>(n, INF));

        for (auto&& edge : edges) {
            dist[edge[0]][edge[1]] = 1;
            dist[edge[1]][edge[0]] = 1;
        }
        warshall_floyd(dist);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (group[i] == group[j]) {
                    ans += dist[i][j];
                }
            }
        }

        return ans;
    }

    static void dfs(const vector<vector<int>>& graph, const vector<int>& group, int cur_node, int from, int cur_group, vector<map<int, long long>>& dp) {
        auto& cur_map = dp[cur_node];
        for (auto&& next : graph[cur_node]) {
            if (next != from) {
                dfs(graph, group, next, cur_node, cur_group, dp);
                for (auto&& [target, cost] : dp[next]) {
                    cur_map.insert({ target, cost + 1LL });
                }
            }
        }
        if (group[cur_node] == cur_group) {
            cur_map.insert({ cur_node, 0LL });
        }
    }
    static void dfs2(const vector<vector<int>>& graph, const vector<int>& group, int cur_node, int from, int cur_group, vector<map<int, long long>>& dp, long long& total) {
        if (group[cur_node] == cur_group) {
            for (auto&& [_, cost] : dp[cur_node]) {
                total += cost;
            }
        }
        auto& cur_map = dp[cur_node];
        for (auto&& next : graph[cur_node]) {
            if (next != from) {
                dfs(graph, group, next, cur_node, cur_group, dp);
                for (auto&& [target, cost] : dp[next]) {
                    cur_map.insert({ target, cost + 1LL });
                }
            }
        }
        if (group[cur_node] == cur_group) {
            cur_map.insert({ cur_node, 0LL });
        }
    }
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }
        map<int, vector<int>> group_map;
        for (int i = 0; i < n; i++) {
            group_map[group[i]].emplace_back(i);
        }

        long long ans = 0;
        for (auto&& [cur_group, nodes] : group_map) {
            vector<map<int, long long>> dp(n);
            dfs(graph, group, nodes[0], -1, cur_group, dp);

        }
        return ans;
    }
};
static void test(int n, vector<vector<int>>&& edges, vector<int>&& group) {
    cout << Solution().interactionCosts(n, edges, group) << endl;
}
static void run() {
    test(3, get_matrix_int("[[0,1],[1,2]]"), get_list_int("[1,1,1]"));
    test(3, get_matrix_int("[[0,1],[1,2]],"), get_list_int("[3,2,3]"));
    test(4, get_matrix_int("[[0,1],[0,2],[0,3]]"), get_list_int("[1,1,4,4]"));
}
}

int main()
{
    //problem1::run();
    //problem2::run();
    //problem3::run();
    problem4::run();
    return 0;
}