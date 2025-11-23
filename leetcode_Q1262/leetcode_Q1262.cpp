#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        const auto n = size(nums);
        vector<vector<long long>> dp(n, vector<long long>(4, -1));
        dp[0][nums[0] % 3] = nums[0];
        for (int i = 1; i < n; i++) {
            dp[i][nums[i] % 3] = nums[i];
            for (int j = 0; j <= 3; j++) {
                if (dp[i - 1][j] >= 0) {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j]);
                    const auto index = (j + nums[i]) % 3;
                    dp[i][index] = max(dp[i][index], dp[i - 1][j] + nums[i]);
                }
            }
        }
        const auto max_value = dp.back()[0];
        if (max_value < 0) { return 0LL; }
        return max_value;
    }
};

static void test(vector<int>&& nums) {
    cout << Solution().maxSumDivThree(nums) << endl;
}

int main()
{
    test(get_list_int("[3,6,5,1,8]"));
    test(get_list_int("[4]"));
    test(get_list_int("[1,2,3,4,4]"));

    return 0;
}