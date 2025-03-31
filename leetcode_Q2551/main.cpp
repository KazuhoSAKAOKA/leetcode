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

    static long long mle(const vector<int>& weights, int k) {
        const auto n = size(weights);
        vector<vector<vector<long long>>> dp(k, vector<vector<long long>>(n, vector<long long>(2, -1)));

        for (int j = 0; j < n - k + 1; j++) {
            dp[0][j][0] = dp[0][j][1] = weights[0] + weights[j];
        }

        for (int i = 1; i < k; i++) {
            for (int j = i; j < n - (k - i) + 1; j++) {
                long long cur_min = LLONG_MAX;
                long long cur_max = LLONG_MIN;
                for (int l = i; l <= j; l++) {
                    cur_min = min(cur_min, dp[i - 1][l - 1][0] + weights[l] + weights[j]);
                    cur_max = max(cur_max, dp[i - 1][l - 1][1] + weights[l] + weights[j]);
                }
                dp[i][j][0] = cur_min;
                dp[i][j][1] = cur_max;
            }
        }
        return dp[k - 1][n - 1][1] - dp[k - 1][n - 1][0];
    }

    long long putMarbles(vector<int>& weights, int k) {
        const auto n = size(weights);
        vector<long long> sums(n - 1);
        for (int i = 0; i < n - 1; i++) {
            sums[i] = weights[i] + weights[i + 1];
        }
        sort(begin(sums), end(sums));
        long long ans = 0;
        for (int i = 0; i < k - 1; i++) {
            ans += sums[n - 2 - i] - sums[i];
        }
        return ans;
    }
};

void test(vector<int>&& weights, int k) {
    cout << Solution().putMarbles(weights, k) << endl;
}

int main() {
    test(get_list_int("[1,3,5,1]"), 2);
    test(get_list_int("[1, 3]"), 2);
    return 0;
}