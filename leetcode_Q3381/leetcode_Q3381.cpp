// leetcode_Q3381.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <climits>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    static long long mle(vector<int>& nums, int k) {
        const auto n = size(nums);
        if (n < k) {
            return 0LL;
        }
        if (n == 1 && k == 1) {
            return nums[0];
        }
        vector<vector<long long>> dp(n, vector<long long>(k, LLONG_MIN));
        long long max_sum = LLONG_MIN;

        dp[0][1 % k] = nums[0];
        max_sum = max(max_sum, dp[0][0]);
        for (int i = 1; i < n; i++) {
            dp[i][1 % k] = static_cast<long long>(nums[i]);
            for (int j = 0; j < k; j++) {
                if (dp[i - 1][j] > LLONG_MIN) {
                    dp[i][(j + 1) % k] = max(dp[i][(j + 1) % k], dp[i - 1][j] + nums[i]);
                }
            }
            max_sum = max(max_sum, dp[i][0]);
        }

        return max_sum;
    }

    long long maxSubarraySum(vector<int>& nums, int k) {
        const int n = size(nums);
        if (n < k) {
            return 0LL;
        }
        if (n == 1 && k == 1) {
            return nums[0];
        }

        vector<long long> prefix_sums(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + nums[i];
        }

        long long max_sum = LLONG_MIN;

        vector<long long> streak_sums(k);
        for (int i = 0; i < min(k, n - k + 1); i++) {
            const auto cur_sum = prefix_sums[i + k] - prefix_sums[i];
            max_sum = max(max_sum, cur_sum);
            streak_sums[i] = cur_sum;
        }

        for (int i = k; i <= n - k; i++) {
            const auto cur_sum = prefix_sums[i + k] - prefix_sums[i];
            streak_sums[i % k] = max(cur_sum, streak_sums[i % k] + cur_sum);
            max_sum = max(max_sum, streak_sums[i % k]);
        }

        return max_sum;
    }
};

static void test(vector<int>&& nums, int k) {
    cout << Solution().maxSubarraySum(nums, k) << endl;
}

int main()
{
    test(get_list_int("[3,-11,8]"), 1);
    test(get_list_int("[-7,-2]"), 2);

    test(get_list_int("[-1,-2,-3,-4,-5]"), 4);
    test(get_list_int("[-5,1,2,-3,4]"), 2);

    test(get_list_int("[-7,-9]"), 1);
    test(get_list_int("[-8]"), 1);

    return 0;
}