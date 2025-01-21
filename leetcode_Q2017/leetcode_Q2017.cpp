// leetcode_Q2017.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        const size_t N = size(grid.front());
        vector<long long> prefix_sums_upper(N + 1);
        vector<long long> prefix_sums_lower(N + 1);

        for (int i = 0; i < N; i++) {
            prefix_sums_upper[i + 1] = prefix_sums_upper[i] + grid[0][i];
            prefix_sums_lower[i + 1] = prefix_sums_lower[i] + grid[1][i];
        }

        long long min_score = LLONG_MAX;
        for (int i = 0; i < N; i++) {
            const auto upper_score = prefix_sums_upper[N] - prefix_sums_upper[i + 1];
            const auto lower_score = prefix_sums_lower[i] - prefix_sums_lower[0];
            const auto second_robot_score = max(upper_score, lower_score);
            min_score = min(min_score, second_robot_score);
        }
        return min_score;
    }
};

void test(vector<vector<int>>&& grid) {
    cout << Solution().gridGame(grid) << endl;
}

int main()
{
    test(get_matrix_int("[[2,5,4],[1,5,1]]"));
    test(get_matrix_int("[[3,3,1],[8,5,2]]"));
    test(get_matrix_int("[[1,3,1,15],[1,3,3,1]]"));
    return 0;
}
