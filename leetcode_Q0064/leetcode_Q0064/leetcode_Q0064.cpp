// leetcode_Q0064.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        const int YCount = grid.size();
        const int XCount = grid.front().size();
        vector<vector<int>> dp(YCount, vector<int>(XCount, 0));

        dp[0][0] = grid[0][0];

        for (auto i = 1; i < YCount; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (auto j = 1; j < XCount; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }
        for (auto i = 1; i < YCount; i++) {
            for (auto j = 1; j < XCount; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[YCount - 1][XCount - 1];
    }
};
void test(vector<vector<int>>&& grid) {
    cout << Solution().minPathSum(grid) << endl;
}


int main()
{
    test({ {1,3,1 }, { 1,5,1 }, { 4,2,1 }, });
    test({ {1,2,3}, {4,5,6}, });
}

