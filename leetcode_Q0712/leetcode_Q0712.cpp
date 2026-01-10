#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        const auto n = size(s1);
        const auto m = size(s2);
        constexpr int INF = INT_MAX;
        vector<vector<int>> dp(n, vector<int>(m, INF));
        const int total = 
            accumulate(cbegin(s1), cend(s1), 0, [](int v, char c) { return v + static_cast<int>(c); })+
            accumulate(cbegin(s2), cend(s2), 0, [](int v, char c) { return v + static_cast<int>(c); });


        int value = 0;
        for (int i = 0; i < n; i++) {
            if (s1[i] == s2[0]) {
                value = static_cast<int>(s2[0]);
            }
            dp[i][0] = value;
        }
        value = 0;
        for (int j = 0; j < m; j++) {
            if (s1[0] == s2[j]) {
                value = static_cast<int>(s1[0]);
            }
            dp[0][j] = value;
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                dp[i][j] = max(max(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1] + (s1[i] == s2[j] ? static_cast<int>(s1[i]) : 0));
            }
        }
        return total - 2 * dp.back().back();
    }
};
static void test(string&& s1, string&& s2) {
    cout << Solution().minimumDeleteSum(s1, s2) << endl;
}
int main()
{
    test("sea", "eat");
    test("delete", "leet");
    return 0;
}