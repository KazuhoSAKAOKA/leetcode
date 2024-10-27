// leetcode_Q1277.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#include <vector>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:

    static int get_sums(const vector<vector<int>>& prefix_sum2d, int sy, int sx, int ey, int ex) {
        return prefix_sum2d[ey][ex] - prefix_sum2d[ey][sx] - prefix_sum2d[sy][ex] + prefix_sum2d[sy][sx];
    }


    int countSquares(vector<vector<int>>& matrix) {
        const auto H = size(matrix);
        const auto W = size(matrix.front());
        vector<vector<int>> prefix_sums(H + 1, vector<int>(W + 1));

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prefix_sums[i + 1][j + 1] = prefix_sums[i + 1][j] + matrix[i][j];
            }
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                prefix_sums[i + 1][j + 1] += prefix_sums[i][j + 1];
            }
        }
        int count = 0;
        for (int sy = 0; sy < H; sy++) {
            for (int sx = 0; sx < W; sx++) {
                const int len = min(H - sy, W - sx);
                for (int l = 1; l <= len; l++) {
                    const auto ey = sy + l;
                    const auto ex = sx + l;
                    const auto expected = (ey - sy) * (ex - sx);
                    const auto actual = get_sums(prefix_sums, sy, sx, ey, ex);
                    if (expected == actual) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};

void test(vector<vector<int>>&& matrix) {
    cout << Solution().countSquares(matrix) << endl;
}

int main()
{
    test(get_matrix_int("[[0,1,1,1],[1,1,1,1],[0,1,1,1]]"));
    test(get_matrix_int("[[1,0,1],[1,1,0],[1,1,0]]"));
    return 0;
}