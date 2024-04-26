// leetcode_Q1289.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static pair<int, int> get_min_second(const vector<int>& values) {
        int min_value = INT_MAX;
        int min2_value = INT_MAX - 1;
        int min_index = -1;
        int min2_index = -1;
        for (int i = 0; i < values.size(); i++) {
            if (values[i] < min_value) {
                min2_index = min_index;
                min2_value = min_value;
                min_index = i;
                min_value = values[i];
            }
            else if (values[i] < min2_value) {
                min2_index = i;
                min2_value = values[i];
            }
        }
        return make_pair(min_index, min2_index);
    }


    int minFallingPathSum(vector<vector<int>>& grid) {
        if (grid.size() < 2) {
            return grid[0][0];
        }

        vector<vector<int>> dp(grid.size(), vector<int>(grid.front().size(), 0));
        for (int i = 0; i < grid.front().size(); i++) {
            dp[0][i] = grid[0][i];
        }

        for (int i = 1; i < grid.size(); i++) {
            const auto [min_index, min2_index] = get_min_second(dp[i - 1]);

            for (int j = 0; j < grid.front().size(); j++) {
                if (j == min_index) {
                    dp[i][j] = dp[i - 1][min2_index] + grid[i][j];
                }
                else {
                    dp[i][j] = dp[i - 1][min_index] + grid[i][j];
                }
            }
        }

        const auto it = min_element(cbegin(dp[grid.size() - 1]), cend(dp[grid.size() - 1]));
        return *it;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().minFallingPathSum(grid) << endl;
}
int main() {
    test({ {1,99,99},{0,2,1,},{99,99,4} });
    test({ {-73, 61, 43, -48, -36}, { 3, 30, 27, 57, 10}, { 96, -76, 84, 59, -15}, { 5, -49, 76, 31, -7}, { 97, 91, 61, -46, 67} });
    test({ {3,2,1,},{6,5,4, },{9,8,7,} });
    test({ {1,2,3,},{6,5,4, },{7,8,9,} });
    test({ {1,2,3,},{4,5,6, },{7,8,9,} });
    test({ {7} });
}