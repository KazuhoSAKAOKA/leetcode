#include <iostream>
#include <vector>
#include <map>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        const auto n = size(prices);
        constexpr long long INF = LLONG_MIN / 2;
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(k + 1, vector<long long>(3, INF)));

        dp[0][0][0] = 0;
        dp[0][0][1] = -prices[0];
        dp[0][0][2] = prices[0];
        for (int i = 1; i < n; i++) {
            const auto cur_price = prices[i];
            for (int j = k - 1; j >= 0; j--) {
                dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0]);
                dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][1]);
                dp[i][j][2] = max(dp[i][j][2], dp[i - 1][j][2]);

                dp[i][j + 1][0] = max(dp[i][j + 1][0], max(dp[i - 1][j][1] + prices[i], dp[i - 1][j][2] - prices[i]));
                dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j][0] - prices[i]);
                dp[i][j][2] = max(dp[i][j][2], dp[i - 1][j][0] + prices[i]);
            }
            dp[i][k][0] = max(dp[i][k][0], dp[i - 1][k][0]);
        }

        long long max_profit = 0LL;
        for (auto&& v : dp.back()) {
            max_profit = max(max_profit, v[0]);
        }
        return max_profit;
    }
};

static void test(vector<int>&& prices, int k) {
    cout << Solution().maximumProfit(prices, k) << endl;
}

int main()
{
    test(get_list_int("[1,7,9,8,2]"), 2);
    test(get_list_int("[12,16,19,19,8,1,19,13,9]"), 3);
    return 0;
}