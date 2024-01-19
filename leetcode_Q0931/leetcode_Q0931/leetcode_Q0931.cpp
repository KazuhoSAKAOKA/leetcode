// leetcode_Q0931.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) { return 0; }
        const int width = matrix.front().size();
        if (width == 0) { return 0; }
        if (width == 1) {
            return accumulate(cbegin(matrix), cend(matrix), 0, [](const auto& before, const auto& list) { return before + list[0]; });
        }
        vector<vector<int>> dp(matrix.size() + 1, vector<int>(width, 0));

        for (int i = 1; i < matrix.size() + 1; i++) {
            const auto index = i - 1;
            dp[i][0] = min(dp[index][0], dp[index][1]) + matrix[index][0];
            for (int j = 1; j < width - 1; j++) {
                dp[i][j] = min(min(dp[index][j - 1], dp[index][j]), dp[index][j + 1]) + matrix[index][j];
            }
            dp[i][width - 1] = min(dp[index][width - 2], dp[index][width - 1]) + matrix[index][width - 1];
        }
        int min_value = INT_MAX;
        for (int j = 0; j < width; j++) {
            min_value = min(min_value, dp[matrix.size()][j]);
        }
        return min_value;
    }
};

void test(vector<vector<int>>&& matrix) {
    cout << Solution().minFallingPathSum(matrix) << endl;
}


int main()
{
    test({
        {2, 1, 3},
        { 6, 5, 4},
        { 7, 8, 9}
    });

    test({
        { -19, 57},
        { -40, -5},
        });

    test({
        { -48},
        });
}