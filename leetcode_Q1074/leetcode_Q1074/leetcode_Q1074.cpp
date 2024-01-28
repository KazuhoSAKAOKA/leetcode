// leetcode_Q1074.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


class Solution {
public:

    static int calc_sum_matrix(const vector<vector<int>>& sum_matrix, int i1, int j1, int i2, int j2) {
        return sum_matrix[i2 + 1][j2 + 1] - sum_matrix[i1][j2 + 1] - sum_matrix[i2 + 1][j1] + sum_matrix[i1][j1];
    }

    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        const int N = matrix.size();
        const int M = matrix.front().size();
        vector<vector<int>> total_sums(N + 1, vector<int>(M + 1, 0));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                total_sums[i][j] = total_sums[i][j - 1] + matrix[i - 1][j - 1];
            }
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                total_sums[i][j] += total_sums[i - 1][j];
            }
        }

        int count = 0;
        for (int i1 = 0; i1 < N; i1++) {
            for (int i2 = i1; i2 < N; i2++) {
                for (int j1 = 0; j1 < M; j1++) {
                    for (int j2 = j1; j2 < M; j2++) {
                        if (calc_sum_matrix(total_sums, i1, j1, i2, j2) == target) {
                            count++;
                        }
                    }
                }
            }
        }
        return count;
    }
};


void test(vector<vector<int>>&& matrix, int target) {
    cout << Solution().numSubmatrixSumTarget(matrix, target) << endl;
}


int main()
{
    test({ {0,1,1,1,0,1},{0,0,0,0,0,1},{0,0,1,0,0,1},{1,1,0,1,1,0},{1,0,0,1,0,0} }, 0);
    test({ {0,1,0},{1,1,1},{0,1,0} }, 0);
    test({ {1,-1},{-1,1} }, 0);
    test({ {904} }, 0);
}