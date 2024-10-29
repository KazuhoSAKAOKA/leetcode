// leetcode_Q2684.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        const auto W = size(grid.front());
        const auto H = size(grid);
        vector<vector<int>> dp(W, vector<int>(H, -1));
        const vector<int> movables{ -1,0,1 };
        int max_moves = 0;
        for (int j = 0; j < H; j++) {
            dp[0][j] = 0;
        }

        for (int i = 1; i < W; i++) {
            for (int j = 0; j < H; j++) {
                for (int moveval : movables) {
                    const auto v = j + moveval;
                    if (0 <= v && v < H && 0 <= dp[i - 1][v]) {
                        if (grid[v][i - 1] < grid[j][i]) {
                            dp[i][j] = max(dp[i][j], dp[i - 1][v] + 1);
                        }
                    }
                    max_moves = max(max_moves, dp[i][j]);
                }
            }
        }
        return max_moves;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().maxMoves(grid) << endl;
}
int main()
{
    test(get_matrix_int("[[3,2,4],[2,1,9],[1,1,7]]"));
    test(get_matrix_int("[[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]"));
    return 0;
}