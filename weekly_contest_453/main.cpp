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

    static bool checkeq(const vector<int>& nums, int k, int target) {
        const int n = size(nums);
        int op_count = 0;
        int next_value;
        if (nums[0] == target) {
            next_value = nums[1];
        }
        else {
            op_count++;
            next_value = -1 * nums[1];
        }
        for (int i = 1; i < n - 1; i++) {
            if (next_value != target) {
                next_value = -1 * nums[i + 1];
                op_count++;
                if (op_count > k) {
                    return false;
                }
            }
            else {
                next_value = nums[i + 1];
            }
        }
        if (next_value == target) {
            return true;
        }
        return false;
    }

    bool canMakeEqual(vector<int>& nums, int k) {
        const auto n = size(nums);
        if (n == 1) { return true; }
        const auto v1 = checkeq(nums, k, 1);
        const auto v2 = checkeq(nums, k, -1);
        return v1 || v2;
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().canMakeEqual(nums, k) << endl;
}

static void run() {
    test(get_list_int("[1,-1,1,-1,1]"), 3);
    test(get_list_int("[-1,-1,-1,1,1,1]"), 5);
}
}
namespace problem2 {
constexpr size_t MODULO = 1e9 + 7;
class Solution {
public:
    static long long factorial_mod(long long n) {
        if (n == 1) {
            return 1;
        }
        return (n * factorial_mod(n - 1)) % MODULO;
    }
    int countPermutations(vector<int>& complexity) {
        const auto n = size(complexity);
        int min_value = complexity[0];
        for (int i = 1; i < n; i++) {
            if (complexity[i] < min_value) {
                return 0;
            }
        }
        return factorial_mod(n - 1);
    }
};
void test(vector<int>&& complexity) {
    cout << Solution().countPermutations(complexity) << endl;
}
static void run() {
    test(get_list_int("[1,2,3]"));
    test(get_list_int("[3,3,3,4,4,4]"));
}
}
namespace problem3 {
constexpr size_t MODULO = 1e9 + 7;
class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const auto n = size(nums);
        vector<map<pair<int, int>, long long>> dp(n - 1);
        {
            const auto cur_min = min(nums[0], nums[1]);
            const auto cur_max = max(nums[0], nums[1]);
            if (cur_max - cur_min <= k) {
                dp[0][{cur_min, cur_max }] += 1LL;
            }
            dp[0][{nums[1], nums[1]}] += 1;
        }
        for (int i = 1; i < n - 1; i++) {
            for (auto&& [p1, count] : dp[i - 1]) {
                const auto& [cur_min, cur_max] = p1;
                const auto new_min = min(cur_min, nums[i + 1]);
                const auto new_max = max(cur_max, nums[i + 1]);
                if (new_max - new_min <= k) {
                    dp[i][{new_min, new_max }] += count;
                    dp[i][{new_min, new_max }] %= MODULO;
                }
                dp[i][{nums[i + 1], nums[i + 1]}] += count;
                dp[i][{nums[i + 1], nums[i + 1]}] %= MODULO;
            }
        }

        long long ans = 0;
        for (auto&& [_, count] : dp.back()) {
            ans += count;
            ans %= MODULO;
        }

        return ans;
    }
};
static void test(vector<int>&& nums, int k) {
    cout << Solution().countPartitions(nums, k) << endl;
}
static void run() {
    test(get_list_int("[13,23,25,2,7]"), 15);
    test(get_list_int("[9,4,1,3,7]"), 4);
    test(get_list_int("[3,3,4]"), 0);
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