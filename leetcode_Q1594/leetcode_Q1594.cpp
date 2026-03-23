
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
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"

using namespace std;

class Solution {
public:
    template <typename T>
    static T min_opt(const optional<T>& v1, const T& v2) {
        if (v1.has_value()) {
            return min(v1.value(), v2);
        }
        return v2;
    }
    template <typename T>
    static T max_opt(const optional<T>& v1, const T& v2) {
        if (v1.has_value()) {
            return max(v1.value(), v2);
        }
        return v2;
    }

    static pair<long long, long long> rec(const vector<vector<int>>& grid, int y, int x) {
        const auto n = size(grid);
        const auto m = size(grid.front());
        if (y == n - 1 && x == m - 1) {
            return { grid.back().back(),grid.back().back() };
        }
        const long long cur = grid[y][x];
        optional<long long> min_value = nullopt;
        optional<long long> max_value = nullopt;
        if (x < m - 1) {
            const auto [min_v, max_v] = rec(grid, y, x + 1);
            const auto v1 = min_v * cur;
            const auto v2 = max_v * cur;
            min_value = min_opt(min_value, min(v1, v2));
            max_value = max_opt(max_value, max(v1, v2));
        }
        if (y < n - 1) {
            const auto [min_v, max_v] = rec(grid, y + 1, x);
            const auto v1 = min_v * cur;
            const auto v2 = max_v * cur;
            min_value = min_opt(min_value, min(v1, v2));
            max_value = max_opt(max_value, max(v1, v2));
        }
        return { min_value.value(), max_value.value()};
    }
    static int tle(vector<vector<int>>& grid) {
        constexpr long long MODULO = 1e9 + 7;
        const auto [v1, v2] = rec(grid, 0, 0);
        if (v1 < 0 && v2 < 0) { return -1; }
        return max(v1, v2) % MODULO;
    }

    int maxProductPath(vector<vector<int>>& grid) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(grid);
        const auto m = size(grid.front());

        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(m, vector<long long>(2)));
        dp[0][0][0] = dp[0][0][1] = grid[0][0];
        for (int i = 1; i < n; i++) {
            dp[i][0][0] = dp[i][0][1] = dp[i - 1][0][0] * grid[i][0];
        }
        for (int j = 1; j < m; j++) {
            dp[0][j][0] = dp[0][j][1] = dp[0][j - 1][0] * grid[0][j];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                const auto v1 = dp[i - 1][j][0] * grid[i][j];
                const auto v2 = dp[i - 1][j][1] * grid[i][j];
                const auto v3 = dp[i][j - 1][0] * grid[i][j];
                const auto v4 = dp[i][j - 1][1] * grid[i][j];
                dp[i][j][0] = min(min(v1, v2), min(v3, v4));
                dp[i][j][1] = max(max(v1, v2), max(v3, v4));

            }
        }
        const auto& goal = dp.back().back();
        if (goal[0] < 0 && goal[1] < 0) { return -1; }
        return max(goal[0], goal[1]) % MODULO;
    }
};

static void test(vector<vector<int>>&& grid) {
    cout << Solution().maxProductPath(grid) << endl;
}

int main(){
    test(get_matrix_int("[[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]"));
    test(get_matrix_int("[[1,-2,1],[1,-2,1],[3,-4,1]]"));
    test(get_matrix_int("[[1,3],[0,-4]]"));
    return 0;
}