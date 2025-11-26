#include <iostream>
#include <vector>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        const auto n = size(grid);
        const auto m = size(grid.front());
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(m, vector<long long>(k + 1, 0LL)));
        constexpr long long MODULO = 1e9 + 7;
        dp[0][0][grid[0][0] % k] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k1 = 0; k1 <= k; k1++) {
                    if (dp[i][j][k1] > 0) {
                        if (j + 1 < m) {
                            const auto cost = grid[i][j + 1];
                            dp[i][j + 1][(k1 + cost) % k] += dp[i][j][k1];
                            dp[i][j + 1][(k1 + cost) % k] %= MODULO;
                        }
                        if (i + 1 < n) {
                            const auto cost = grid[i + 1][j];
                            dp[i + 1][j][(k1 + cost) % k] += dp[i][j][k1];
                            dp[i + 1][j][(k1 + cost) % k] %= MODULO;
                        }
                    }
                }
            }
        }

        return static_cast<int>(dp[n - 1][m - 1][0]);
    }
};

static void test(vector<vector<int>>&& grid, int k) {
    cout << Solution().numberOfPaths(grid, k) << endl;
}

int main()
{
    test(get_matrix_int("[[7,3,4,9],[2,3,6,2],[2,3,7,0]]"), 1);
    test(get_matrix_int("[[5,2,4],[3,0,5],[0,7,2]]"), 3);
    test(get_matrix_int("[[0,0]]"), 5);

    return 0;
}