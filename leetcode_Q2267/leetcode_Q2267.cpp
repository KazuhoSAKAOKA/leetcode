
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
#include <bitset>
#include <sstream>
#include <optional>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


class Solution {
public:

    static optional<int> check(const int& value, char c) {
        if (c == '(') {
            return value + 1;
        }
        if (value == 0) {
            return nullopt;
        }
        return value - 1;
    }

    static void transit(set<int>& dest, const set<int>& source, char c) {
        for (auto&& a : source) {
            auto temp = check(a, c);
            if (temp.has_value()) {
                dest.insert(temp.value());
            }
        }
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        const auto n = size(grid);
        const auto m = size(grid[0]);
        if (grid[0][0] != '(') { return false; }
        if (grid[n - 1][m - 1] != ')') { return false; }
        vector<vector<set<int>>> dp(n, vector<set<int>>(m));

        dp[0][0].insert(1);

        for (size_t i = 1; i < n; i++) {
            transit(dp[i][0], dp[i - 1][0], grid[i][0]);
        }
        for (size_t j = 1; j < m; j++) {
            transit(dp[0][j], dp[0][j - 1], grid[0][j]);
        }

        for (size_t i = 1; i < n; i++) {
            for (size_t j = 1; j < m; j++) {
                transit(dp[i][j], dp[i][j - 1], grid[i][j]);
                transit(dp[i][j], dp[i - 1][j], grid[i][j]);
            }
        }

        return dp[n - 1][m - 1].count(0) != 0;
    }
};

static void test(vector<vector<char>>&& grid) {
    cout << Solution().hasValidPath(grid) << endl;
}
int main() {
    test({ {'(','(','('},{')','(',')'},{'(','(',')'},{'(','(',')'} });
    test({ {')',')'},{'(','('} });
    return 0;
}
