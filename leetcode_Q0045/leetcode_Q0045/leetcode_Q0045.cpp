// leetcode_Q0045.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), INT_MAX);//その地点に到達できる最小ステップ

        dp[0] = 0;
        for (auto i = 0; i < nums.size() - 1; i++) {
            const auto limit = min(static_cast<int>(nums.size()) - 1 - i, nums[i]);
            for (auto step = 1; step <= limit; step++) {
                dp[i + step] = min(dp[i] + 1, dp[i + step]);
            }
        }

        return dp[nums.size() - 1]; 
    }
};

void test(vector<int>&& nums) {
    cout << Solution().jump(nums) << endl;
}


int main()
{
    test({ 1,2,3 });
    test({ 2,3,1,1,4 });
    test({ 2,3,0,1,4 });
}

