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
    static vector<bool> eratosthenes(int n) {
        vector<bool> candidates(n + 1, true);
        candidates[0] = false;
        candidates[1] = false;
        const auto limit = sqrt(n);
        int current = 2;
        while (current <= limit) {
            if (candidates[current]) {
                for (int i = 2; i * current <= n; i++) {
                    candidates[i * current] = false;
                }
            }
            current++;
        }
        return candidates;
    }

    bool checkPrimeFrequency(vector<int>& nums) {
        map<int, int>freqs;
        for (auto&& num : nums) {
            freqs[num]++;
        }
        const auto primes = eratosthenes(100);
        for (auto&& [_, freq] : freqs) {
            if (primes[freq]) {
                return true;
            }
        }
        return false;
    }
};
static void test(vector<int>&& nums) {
    cout << Solution().checkPrimeFrequency(nums) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4,5,4]"));
    test(get_list_int("[1,2,3,4,5]"));
    test(get_list_int("[2,2,2,4,4]"));
}
}
namespace problem2 {
class Solution {
public:

    static void add_create_ways(int coin, vector<int>& ways) {
        const auto n = size(ways);
        vector<int> appends(n);
        
        for (int amount = coin; amount <= n; amount += coin) {
            appends[amount - 1] = 1;
        }

        for (int i = 0; i < n; i++) {
            if (ways[i] > 0) {
                for (int amount = i + coin + 1; amount <= n; amount += coin) {
                    appends[amount - 1] += ways[i];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            ways[i] += appends[i];
        }
    }
    vector<int> findCoins(vector<int>& numWays) {
        const auto n = size(numWays);

        vector<int> current_creates(n);
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            const int cur_amount = i + 1;
            if (numWays[i] == 0) {
                if (current_creates[i] != 0) {
                    return {};
                }
            }
            else {
                if (numWays[i] == current_creates[i]) {
                }
                else if (numWays[i] < current_creates[i]) {
                    return {};
                }
                else {
                    const auto diff = numWays[i] - current_creates[i];
                    if (diff == 1) {
                        ans.emplace_back(cur_amount);
                        add_create_ways(cur_amount, current_creates);
                    }
                    else {
                        return {};
                    }
                }
            }
        }

        return ans;
    }
};
void test(vector<int>&& numWays) {
    output(Solution().findCoins(numWays));
}
static void run() {
    test(get_list_int("[0,1,0,2,0,3,0,4,0,5]"));
    test(get_list_int("[1,2,2,3,4]"));
    test(get_list_int("[1,2,3,4,15]"));
}
}
namespace problem3 {
class Solution {
public:
    static long long dfs_calc(const vector<vector<int>>& graph, vector<int>& cost, int current, int from, long long current_cost, vector<long long>& dp) {
        bool exist = false;
        long long max_cost = -1;

        set<long long> childs;
        for (auto&& next : graph[current]) {
            if (next != from) {
                exist = true;
                max_cost = max(max_cost, dfs_calc(graph, cost, next, current, current_cost + cost[current], dp));
                childs.insert(dp[next]);
            }
        }
        if (!exist) {
            //leaf;
            dp[current] = current_cost + cost[current];
            return dp[current];
        }
        if (size(childs) == 1) {
            dp[current] = *cbegin(childs);
        }
        else {
            dp[current] = -1;
        }
        return max_cost;
    }

    static int dfs_solve(const vector<vector<int>>& graph, const vector<long long>& dp, long long target_cost, int current, int from) {
        if (dp[current] >= 0) {
            if (dp[current] < target_cost) {
                return 1;
            }
            return 0;
        }

        int total_count = 0;
        for (auto&& next : graph[current]) {
            if (next != from) {
                total_count += dfs_solve(graph, dp, target_cost, next, current);
            }
        }
        return total_count;
    }


    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            graph[edge.front()].emplace_back(edge.back());
            graph[edge.back()].emplace_back(edge.front());
        }
        vector<long long> dp(n);
        const auto max_cost = dfs_calc(graph, cost, 0, -1, 0, dp);
        return dfs_solve(graph, dp, max_cost, 0, -1);
    }
};
void test(int n, vector<vector<int>>&& edges, vector<int>&& cost) {
    cout << Solution().minIncrease(n, edges, cost) << endl;
}

static void run() {
    test(2, get_matrix_int("[[0,1]]"), get_list_int("[1,1]"));
    test(3, get_matrix_int("[[0,1],[0,2]]"), get_list_int("[2,1,3]"));
    test(3, get_matrix_int("[[0,1],[1,2]]"), get_list_int("[5,1,4]"));
    test(5, get_matrix_int("[[0,4],[0,1],[1,2],[1,3]]"), get_list_int("[3,4,1,1,7]"));
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