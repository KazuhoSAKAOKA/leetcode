// leetcode_Q0198.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        vector<vector<int>> dp(nums.size() + 1, vector<int>(2, 0));

        for (int i = 0; i < nums.size(); i++) {
            dp[i + 1][0] = max(dp[i][0], dp[i][1]);
            dp[i + 1][1] = dp[i][0] + nums[i];
        }
        return max(dp[nums.size()][0], dp[nums.size()][1]);
    }
};

void test(vector<int>&& nums) {
    cout << Solution().rob(nums) << endl;
}

int main()
{
    test({ 1,2,3,1 });
    test({ 2,7,9,3,1 });
    test({});

}