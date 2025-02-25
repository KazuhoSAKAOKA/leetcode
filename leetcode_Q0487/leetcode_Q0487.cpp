// leetcode_Q0487.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        vector<vector<int>> dp(size(nums), vector<int>(2));
        int max_streak = 0;
        if (nums[0] == 1) {
            dp[0][0] = 1;
        }
        else {
            dp[0][1] = 1;
        }
        max_streak = max(max_streak, dp[0][0]);
        max_streak = max(max_streak, dp[0][1]);
        for (int i = 1; i < size(nums); i++) {
            if (nums[i] == 1) {
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = dp[i - 1][1] + 1;
            }
            else {
                dp[i][0] = 0;
                dp[i][1] = dp[i - 1][0] + 1;
            }
            max_streak = max(max_streak, dp[i][0]);
            max_streak = max(max_streak, dp[i][1]);
        }
        return max_streak;
    }
};

void test(vector<int>&& nums) {
    cout << Solution().findMaxConsecutiveOnes(nums) << endl;
}

int main()
{
    test(get_list_int("[1,0,1,1,0]"));
    test(get_list_int("[1,0,1,1,0,1]"));
    return 0;
}