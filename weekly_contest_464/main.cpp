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
    template <typename T>
    static
    T gcd(const T& a, const T& b) {
        if (b == 0) { return a; }
        return gcd(b, a % b);
    }
    int gcdOfOddEvenSums(int n) {
        int sum_even = 0;
        int sum_odd = 0;
        for (int i = 0; i < n; i++) {
            sum_even += (i + 1) * 2;
            sum_odd += i * 2 + 1;
        }
        return gcd(sum_even, sum_odd);
    }
}; 
static void test(int n) {
    cout << Solution().gcdOfOddEvenSums(n) << endl;
}

static void run() {
    test(4);
    test(5);
}
}
namespace problem2 {
class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        const auto n = size(nums);
        if (n % k != 0) {
            return false;
        }
        const auto m = n / k;
        unordered_map<int, int> freqs;
        for (auto&& num : nums) {
            freqs[num]++;
        }
        if (size(freqs) < k) {
            return false;
        }
        for (auto&& [_, count] : freqs) {
            if (m < count) {
                return false;
            }
        }
        return true;
    }
};
static void test(vector<int>&& nums, int k) {
    cout << boolalpha << Solution().partitionArray(nums, k) << endl;
}
static void run() {
    test(get_list_int("[1,2,3,4]"), 2);
    test(get_list_int("[3,5,2,2]"), 2);
    test(get_list_int("[1,5,2,3]"), 3);
}
}
namespace problem3 {
class Solution {
public:
    static int dfs(const vector<vector<int>>& graph, const vector<int>& nums, int current, vector<bool>& visited, vector<int>& memo) {
        if (memo[current] >= 0) {
            return memo[current];
        }
        int max_value = nums[current];
        for (auto&& next : graph[current]) {
            if (!visited[next]) {
                visited[next] = true;
                max_value = max(max_value, dfs(graph, nums, next, visited, memo));
                visited[next] = false;
            }
        }
        //memo[current] = max_value;
        return max_value;
    }

    static vector<int> tle(vector<int>& nums) {
        const auto n = size(nums);
        vector<vector<int>> graph(n);
        int current_max = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] > nums[i]) {
                    graph[i].emplace_back(j);
                }
            }
            for (int j = i + 1; j < n; j++) {
                if (nums[j] < nums[i]) {
                    graph[i].emplace_back(j);
                }
            }
        }
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++) {
            vector<bool> visited(n);
            visited[i] = true;
            ans[i] = dfs(graph, nums, i, visited, ans);
        }
        return ans;

    }

    vector<int> maxValue(vector<int>& nums) {
        const auto n = size(nums);
        vector<int> prefixs(n);
        vector<int> suffix_indexes(n);
        int cur_max = 0;
        int cur_min_index = n - 1;
        for (int i = 0; i < n; i++) {
            cur_max = max(cur_max, nums[i]);
            prefixs[i] = cur_max;

            suffix_indexes[n - i - 1] = cur_min_index;
            if (nums[n - i - 1] < nums[cur_min_index]) {
                cur_min_index = n - i - 1;
            }
        }
        vector<int> ans(n);
        ans[n - 1] = cur_max;
        for (int i = n - 2; i >= 0; i--) {
            if ((nums[suffix_indexes[i]] < nums[i]) || (nums[suffix_indexes[i]] < prefixs[i])) {
                ans[i] = max(prefixs[i], ans[suffix_indexes[i]]);
            }
            else {
                ans[i] = prefixs[i];
            }
        }
        return ans;
    }
};
static void test(vector<int>&& nums) {
    output(Solution().maxValue(nums));
}
static void run() {
    test(get_list_int("[2,1,3]"));
    test(get_list_int("[30,21,5,35,24]"));
	test(get_list_int("[1,17,1,6]"));
	test(get_list_int("[2,3,1]"));
	test(get_list_int("[16,4,24,2,3]"));
}
}
namespace problem4 {
class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        const auto n = size(robots);
        const auto m = size(walls);
        vector<int> indexes(n);
        for (int i = 0; i < n; i++) { indexes[i] = i; }
        sort(begin(indexes), end(indexes), [&](int a, int b) { return robots[a] < robots[b];  });
        sort(begin(walls), end(walls));

        int robot_index = 0;
        vector<vector<int>> dp(n + 1, vector<int>(2));
        dp[0][0] = 0;
        dp[0][1] = 0;
        vector<int> tails{ 0, 0 };

        auto get_wall_count = [&](int s, int e)->int{
            auto its = lower_bound(cbegin(walls), cend(walls), s);
            auto ite = upper_bound(cbegin(walls), cend(walls), e);
            return std::distance(its, ite);
        };

        auto get_prev_limit = [&](int index)-> int {
            const auto pos = max(0, robots[indexes[index]] - distance[indexes[index]]);
            if (index == 0) {
                return pos;
            }
            return max(pos, robots[indexes[index - 1]] + 1);
            };

        auto get_prev_fired_limit = [&](int index)-> int {
            const auto pos = max(0, robots[indexes[index]] - distance[indexes[index]]);
            if (index == 0) {
                return pos;
            }
            return max(pos, robots[indexes[index - 1]] + +distance[indexes[index - 1]] + 1);
            };

        auto get_next_limit = [&](int index)-> int {
            const auto pos = robots[indexes[index]] + distance[indexes[index]];
            if (index == n - 1) {
                return pos;
            }
            return min(pos, robots[indexes[index + 1]] - 1);
            };

        for (int i = 0; i < n; i++) {
            const auto& robo_pos = robots[indexes[i]];
            const auto& dist = distance[indexes[i]];
            // 前に撃つ
            // 前のロボットは前に撃った場合
            const auto c1 = get_wall_count(get_prev_limit(i), robo_pos) + dp[i][0];
            // 前のロボットが後ろに撃った場合
            const auto c2 = get_wall_count(get_prev_fired_limit(i), robo_pos) + dp[i][1];
            dp[i + 1][0] = max(c1, c2);

            // 後に撃つ
            dp[i + 1][1] = get_wall_count(robo_pos, get_next_limit(i)) + max(dp[i][0], dp[i][1]);
        }

        return max(dp.back()[0], dp.back()[1]);
    }
};
static void test(vector<int>&& robots, vector<int>&& distance, vector<int>&& walls) {
    cout << Solution().maxWalls(robots, distance, walls) << endl;
}
static void run() {
    test(get_list_int("[4]"), get_list_int("[3]"), get_list_int("[1,10]"));
    test(get_list_int("[10,2]"), get_list_int("[5,1]"), get_list_int("[5,2,7]"));
    test(get_list_int("[1,2]"), get_list_int("[100,1]"), get_list_int("[10]"));
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