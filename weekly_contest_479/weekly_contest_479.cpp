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
    static int binary_reflection(int value) {
        vector<bool> bins;
        for (int i = 0; i < 32; i++) {
            if (value & (1 << i)) {
                bins.emplace_back(true);
            }
            else {
                bins.emplace_back(false);
            }
        }
        int ret = 0;
        int index = 0;
        bool exist = false;
        for (auto it = crbegin(bins); it != crend(bins); ++it) {
            if (exist) {
                if (*it) {
                    ret |= (1 << index);
                }
                index++;
            }
            else {
                if (*it) {
                    exist = true;
                    ret = 1;
                    index = 1;
                }
            }
        }
        return ret;
    }

    vector<int> sortByReflection(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> refs(n);
        vector<int> indexes(n);
        for (int i = 0; i < n; i++) {
            refs[i] = binary_reflection(nums[i]);
            indexes[i] = i;
        }
        sort(begin(indexes), end(indexes), [&](int a, int b) { 
            if (refs[a] == refs[b]) {
                return nums[a] < nums[b];
            }
            return refs[a] < refs[b];
            });
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = nums[indexes[i]];
        }
        return ans;
    }
};
static void test(vector<int>&& nums) {
    output(Solution().sortByReflection(nums));
}
static void run() {
    test(get_list_int("[8,2]"));
    test(get_list_int("[4,5,4]"));
    test(get_list_int("[3,6,5,8]"));
}
}
namespace problem2 {
class Solution {
public:

    static int eratosthenes1(int n) {
        std::vector<bool> candidates(n + 1, true);
        std::vector<bool> candidates2(n + 1, false);
        candidates[0] = false;
        candidates[1] = false;
        int current = 2;
        long long total = 0;
        long long ans = 0;
        while (current <= n) {
            if (candidates[current]) {
                total += current;
                if (total <= n) {
                    candidates2[total] = true;
                }
                if (candidates2[current]) {
                    ans = current;
                }
                for (int i = 2; i * current <= n; i++) {
                    candidates[i * current] = false;
                }
            }
            current++;
        }
        return ans;
    }

    int largestPrime(int n) {
        return eratosthenes1(n);
    }
};
static void test(int n) {
    cout << Solution().largestPrime(n) << endl;
}
static void run() {
    test(5e5);
    test(20);
    test(2);
}
}
namespace problem3 {
class Solution {
public:
    static long long tle(int hp, vector<int>& damage, vector<int>& requirement) {
        const auto n = size(damage);
        long long total_score = 0LL;

        map<long long, long long> bring_hps;
        long long base = 0LL;
        for (int i = 0; i < n; i++) {
            long long cur = static_cast<long long>(hp) + base;
            bring_hps[cur]++;
            base += static_cast<long long>(damage[i]);
            long long cur_requre = base + static_cast<long long>(requirement[i]);
            auto it = bring_hps.lower_bound(cur_requre);
            for (; it != cend(bring_hps); ++it) {
                total_score += it->second;
            }
        }
        return total_score;
    }

    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        const auto n = size(damage);
        vector<long long> prefix_damages(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_damages[i + 1] = prefix_damages[i] + damage[i];
        }

        long long total_score = 0LL;
        long long base = 0LL;
        for (int i = 0; i < n; i++) {
            const auto cur_requrement = prefix_damages[i + 1] + requirement[i] - hp;
            auto it = lower_bound(cbegin(prefix_damages), cend(prefix_damages), cur_requrement);
            const auto index = distance(cbegin(prefix_damages), it);
            if (index <= i) {
                total_score += (i - index + 1);
            }
        }
        return total_score;
    }
};
static void test(int hp, vector<int>&& damage, vector<int>&& requirement) {
    cout << Solution().totalScore(hp, damage, requirement) << endl;
}
static void run() {
    test(11, get_list_int("[3,6,7]"), get_list_int("[4,2,5]"));
    test(2, get_list_int("[10000,1]"), get_list_int("[1,1]"));
}
}
namespace problem4 {
class Solution {
public:
    static int dfs(const vector<vector<int>>& graph, const vector<int>& good, int current, int from, vector<int>& dp) {
        int score = ((good[current] == 1) ? 1 : -1);
        for (auto&& next : graph[current]) {
            if (next != from) {
                const auto child_score = dfs(graph, good, next, current, dp);
                if (child_score >= 0) {
                    score += child_score;
                }
            }
        }
        dp[current] = score;
        return score;
    }

    static void dfs2(const vector<vector<int>>& graph, int current, int from, const vector<int>& dp, int value, vector<int>& ans) {
        ans[current] = value;
        for (auto&& next : graph[current]) {
            if (next != from) {
                const int my_score = (dp[next] < 0) ? value : value - dp[next];
                const int propagate_score = (my_score < 0) ? 0 : my_score;
                dfs2(graph, next, current, dp, propagate_score + dp[next], ans);
            }
        }
    }


    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        vector<vector<int>> graph(n);
        for (auto&& edge : edges) {
            const auto u = edge[0];
            const auto v = edge[1];
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }
        vector<int> dp(n);
        const auto a0 = dfs(graph, good, 0, -1, dp);
        vector<int> ans(n);
        dfs2(graph, 0, -1, dp, a0, ans);
        return ans;
    }
};
static void test(int n, vector<vector<int>>&& edges, vector<int>&& good) {
    output(Solution().maxSubgraphScore(n, edges, good));
}

static void run() {
    test(5, get_matrix_int("[[1,0],[1,2],[1,3],[3,4]]"), get_list_int("[0,1,0,1,1]"));
    test(3, get_matrix_int("[[0,1],[1,2]]"), get_list_int("[1,0,1]"));
    test(2, get_matrix_int("[[0,1]]"), get_list_int("[0,0]"));
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