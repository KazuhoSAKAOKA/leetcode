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

    static pair<int, int> counting(const string& str) {
        const int zeros = count_if(cbegin(str), cend(str), [](char c) { return c == '0'; });
        return { zeros, static_cast<int>(size(str)) - zeros };
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        const auto N = size(strs);
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(m + 1, vector<int>(n + 1)));
        const auto [z0, o0] = counting(strs[0]);
        if (z0 <= m && o0 <= n) {
            dp[0][z0][o0] = 1;
        }
        for (int i = 1; i < N; i++) {
            const auto [z, o] = counting(strs[i]);
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
                    if (j + z <= m && k + o <= n) {
                        dp[i][j + z][k + o] = max(dp[i][j + z][k + o], dp[i - 1][j][k] + 1);
                    }
                }
            }
        }

        int max_subsets = 0;
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= n; k++) {
                max_subsets = max(max_subsets, dp[N - 1][j][k]);
            }
        }
        return max_subsets;
    }
};
static void test(vector<string>&& strs, int m, int n) {
    cout << Solution().findMaxForm(strs, m, n) << endl;
}

int main() {
    test(get_list_str(R"(["10","0001","111001","1","0"])"), 5, 3);
    test(get_list_str(R"(["10","0","1"])"), 1, 1);
    return 0;
}