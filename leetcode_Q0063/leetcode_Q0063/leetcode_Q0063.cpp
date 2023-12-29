// leetcode_Q0063.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        const int YCount = obstacleGrid.size();
        const int XCount = obstacleGrid.front().size();
        vector<vector<int>> dp(YCount, vector<int>(XCount, 0));
        for (int i = 0; i < YCount; i++) {
            if (obstacleGrid[i][0] != 0) { break; }
            dp[i][0] = 1;
        }
        for (int j = 0; j < XCount; j++) {
            if (obstacleGrid[0][j] != 0) { break; }
            dp[0][j] = 1;
        }

        for (int i = 1; i < YCount; i++) {
            for (int j = 1; j < XCount; j++) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[YCount - 1][XCount - 1];
    }
};


void test(vector<vector<int>>&& grid) {
    cout << Solution().uniquePathsWithObstacles(grid) << endl;
}


int main()
{
    test({ {0,0,0},{0,1,0}, {0,0,0} });
    test({ {0,1}, {0,0}, });
}

