#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:

    static int get_manhattan(const vector<int>& a, const vector<int>& b) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
    template <typename T>
    static int popcount_kernighan(T x) {
        int count = 0;
        while (x) {
            x &= (x - 1);
            count++;
        }
        return count;
    }
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        const auto n = size(workers);
        const auto m = size(bikes);
        const auto bit_masks = (1 << n) - 1;
        constexpr int INF = INT_MAX;
        vector<vector<int>> dp(m, vector<int>(bit_masks + 1, INF));

        dp[0][0] = 0;
        for (int j = 0; j < n; j++) {
            dp[0][1 << j] = get_manhattan(bikes[0], workers[j]);
        }
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                const auto cur_bit = 1 << j;
                const auto cur_dist = get_manhattan(bikes[i], workers[j]);
                for (int bitmask = 0; bitmask <= bit_masks; bitmask++) {
                    if (dp[i - 1][bitmask] != INF) {
                        dp[i][bitmask] = min(dp[i][bitmask], dp[i - 1][bitmask]);
                        if ((bitmask & cur_bit) == 0) {
                            dp[i][bitmask | cur_bit] = min(dp[i][bitmask | cur_bit], dp[i - 1][bitmask] + cur_dist);
                        }
                    }
                }
            }
        }
        int min_dist = INT_MAX;
        for (int bitmask = 0; bitmask <= bit_masks; bitmask++) {
            if (popcount_kernighan(bitmask) == n) {
                min_dist = min(min_dist, dp.back()[bitmask]);
            }
        }
        return min_dist;
    }
};
static void test(vector<vector<int>>&& workers, vector<vector<int>>&& bikes) {
    cout << Solution().assignBikes(workers, bikes) << endl;
}
int main() {
    test(get_matrix_int("[[0,0],[1,0],[2,0],[3,0],[4,0]]"), get_matrix_int("[[0,999],[1,999],[2,999],[3,999],[4,999],[5,999]]"));
    test(get_matrix_int("[[0,0],[2,1]]"), get_matrix_int("[[1,2],[3,3]]"));
    test(get_matrix_int("[[0,0],[1,1],[2,0]]"), get_matrix_int("[[1,0],[2,2],[2,1]]"));
    test(get_matrix_int("[[0,0],[1,0],[2,0],[3,0],[4,0]]"), get_matrix_int("[[0,999],[1,999],[2,999],[3,999],[4,999]]"));
    return 0;
}