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
#include <numbers>
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
    int minimumDistance(string word) {
        const auto n = size(word);
        constexpr int INF = INT_MAX / 3;
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(26, vector<int>(27, INF)));
        constexpr int NONE = 26;

        auto get_xy = [](int index)-> pair<int, int> {
            return { index / 6, index % 6 };
            };

        auto get_distance = [&](int a, int b)-> int {
            const auto [y1, x1] = get_xy(a);
            const auto [y2, x2] = get_xy(b);
            return abs(y1 - y2) + abs(x1 - x2);
            };


        dp[0][word[0] - 'A'][NONE] = 0;

        for (int i = 1; i < n; i++) {
            const auto index = static_cast<int>(word[i] - 'A');
            for (int l = 0; l < 26; l++) {
                dp[i][l][index] = min(dp[i][l][index], dp[i - 1][l][NONE]);
                dp[i][index][NONE] = min(dp[i][index][NONE], dp[i - 1][l][NONE] + get_distance(l, index));
                for (int r = 0; r < 26; r++) {
                    dp[i][index][r] = min(dp[i][index][r], dp[i - 1][l][r] + get_distance(l, index));
                    dp[i][l][index] = min(dp[i][l][index], dp[i - 1][l][r] + get_distance(r, index));
                }
            }
        }
        int min_value = INF;
        for (int l = 0; l < 26; l++) {
            for (int r = 0; r < 27; r++) {
                min_value = min(min_value, dp[n - 1][l][r]);
            }
        }
        return min_value;
    }
};

static void test(string&& word) {
    cout << Solution().minimumDistance(word) << endl;
}

int main() {
    test("CAKE");
    test("HAPPY");
    return 0;
}
