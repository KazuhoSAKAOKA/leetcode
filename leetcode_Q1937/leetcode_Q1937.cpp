// leetcode_Q1937.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <cmath>

#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    static long long tle(const vector<vector<int>>&& points) {
        const size_t ROWS = size(points);
        const size_t COLS = size(points.front());
        vector<vector<long long>> dp(ROWS, vector<long long>(COLS));

        for (size_t j = 0; j < COLS; j++) {
            dp[0][j] = points[0][j];
        }

        for (size_t i = 0; i < ROWS - 1; i++) {
            for (size_t j = 0; j < COLS; j++) {
                for (size_t k = 0; k < COLS; k++) {
                    dp[i + 1][k] = max(dp[i + 1][k], points[i + 1][k] + dp[i][j] - abs(static_cast<long long>(j) - static_cast<long long>(k)));
                }
            }
        }
        long long ans = 0;
        for (size_t j = 0; j < COLS; j++) {
            ans = max(ans, dp[ROWS - 1][j]);
        }
        return ans;
    }

    long long maxPoints(vector<vector<int>>& points) {
        const size_t ROWS = size(points);
        const size_t COLS = size(points.front());
        vector<vector<long long>> dp(ROWS, vector<long long>(COLS, 0LL));
        long long prev_left_to_right_score = 0;
        long long prev_right_to_left_score = 0;
        for (size_t j = 0; j < COLS; j++) {
            dp[0][j] = points[0][j];
            prev_left_to_right_score = max(prev_left_to_right_score, points[0][j] - static_cast<long long>(j));
            prev_right_to_left_score = max(prev_right_to_left_score, points[0][j] - static_cast<long long>(COLS - j - 1));
        }

        for (size_t i = 0; i < ROWS - 1; i++) {
            long long current_left_to_right_score = points[i + 1][0] + prev_left_to_right_score;
            long long current_right_to_left_score = points[i + 1][COLS - 1] + prev_right_to_left_score;
            dp[i + 1][0] = current_left_to_right_score;
            dp[i + 1][COLS - 1] = current_right_to_left_score;
            for (size_t j = 1; j < COLS; j++) {
                prev_left_to_right_score = max(prev_left_to_right_score - 1, dp[i][j]);
                dp[i + 1][j] = max(dp[i + 1][j],  points[i + 1][j] + prev_left_to_right_score);
                prev_right_to_left_score = max(prev_right_to_left_score - 1, dp[i][COLS - j - 1]);
                dp[i + 1][COLS - j - 1] = max(dp[i + 1][COLS - j - 1], points[i + 1][COLS - j - 1] + prev_right_to_left_score);
            }
            for (size_t j = 0; j < COLS; j++) {
                dp[0][j] = points[0][j];
                current_left_to_right_score = max(current_left_to_right_score, dp[i + 1][j] - static_cast<long long>(j));
                current_right_to_left_score = max(current_right_to_left_score, dp[i + 1][j] - static_cast<long long>(COLS - j - 1));
            }

            prev_left_to_right_score = current_left_to_right_score;
            prev_right_to_left_score = current_right_to_left_score;
        }
        long long ans = 0;
        for (size_t j = 0; j < COLS; j++) {
            ans = max(ans, dp[ROWS - 1][j]);
        }
        return ans;
    }
};

void test(vector<vector<int>>&& points) {
    cout << Solution().maxPoints(points) << endl;
}
int main()
{
    test(get_matrix_int("[[1,2,3],[1,5,1],[3,1,1]]"));
    test(get_matrix_int("[[0,3,0,4,2],[5,4,2,4,1],[5,0,0,5,1],[2,0,1,0,3]]"));
    test(get_matrix_int("[[1,5],[2,3],[4,2]]"));
    return 0;
}