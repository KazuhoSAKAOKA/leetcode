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
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    static long long dfs(int remain_zero, int remain_one, int limit, string& current, int cur_len_zero, int cur_len_one, map<tuple<int, int, string>, long long>& memo) {
        if (remain_zero == 0 && remain_one == 0) {
            return 1;
        }

        const auto key = make_tuple(remain_zero, remain_one, current.substr(max(0, static_cast<int>(size(current)) - (limit + 1)), limit + 1));
        auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        long long ret = 0LL;
        if (size(current) <= limit) {
            if (size(current) == limit && (cur_len_zero == 0 || cur_len_one == 0)) {
                if (cur_len_zero == 0) {
                    if (remain_zero > 0) {
                        current.push_back('0');
                        ret += dfs(remain_zero - 1, remain_one, limit, current, cur_len_zero + 1, cur_len_one, memo);
                        ret %= MODULO;
                        current.pop_back();
                    }
                }
                else {
                    if (remain_one > 0) {
                        current.push_back('1');
                        ret += dfs(remain_zero, remain_one - 1, limit, current, cur_len_zero, cur_len_one + 1, memo);
                        ret %= MODULO;
                        current.pop_back();
                    }
                }
            }
            else {
                if (remain_zero > 0) {
                    current.push_back('0');
                    ret += dfs(remain_zero - 1, remain_one, limit, current, cur_len_zero + 1, cur_len_one, memo);
                    ret %= MODULO;
                    current.pop_back();
                }
                if (remain_one > 0) {
                    current.push_back('1');
                    ret += dfs(remain_zero, remain_one - 1, limit, current, cur_len_zero, cur_len_one + 1, memo);
                    ret %= MODULO;
                    current.pop_back();
                }
            }
        }
        else {
            int next_len_zero = cur_len_zero;
            int next_len_one = cur_len_one;
            if (current[size(current) - limit - 1] == '0') {
                next_len_zero--;
            }
            else {
                next_len_one--;
            }

            if (next_len_one > 0) {
                if (remain_zero > 0) {
                    current.push_back('0');
                    ret += dfs(remain_zero - 1, remain_one, limit, current, next_len_zero + 1, next_len_one, memo);
                    ret %= MODULO;
                    current.pop_back();
                }
            }
            if (next_len_zero > 0) {
                if (remain_one > 0) {
                    current.push_back('1');
                    ret += dfs(remain_zero, remain_one - 1, limit, current, next_len_zero, next_len_one + 1, memo);
                    ret %= MODULO;
                    current.pop_back();
                }
            }

        }
        memo.insert({ key,ret });
        return ret;
    }

    int numberOfStableArrays(int zero, int one, int limit) {
        if (zero == 0 || one == 0 || limit == 0) { return 0; }
        vector<vector<vector<long long>>> dp(zero + 1, vector<vector<long long>>(one + 1, vector<long long>(2)));
        for (int i = 0; i <= min(zero, limit); i++) { dp[i][0][0] = 1; }
        for (int j = 0; j <= min(one, limit); j++) { dp[0][j][1] = 1; }
        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {
                if (i <= limit) {
                    dp[i][j][0] = dp[i - 1][j][1] + dp[i - 1][j][0];
                }
                else {
                    dp[i][j][0] = dp[i - 1][j][1] + dp[i - 1][j][0] - dp[i - limit - 1][j][1];
                }
                if (dp[i][j][0] < 0) { dp[i][j][0] += MODULO; }
                dp[i][j][0] %= MODULO;

                if (j <= limit) {
                    dp[i][j][1] = dp[i][j - 1][0] + dp[i][j - 1][1];
                }
                else {
                    dp[i][j][1] = dp[i][j - 1][0] + dp[i][j - 1][1] - dp[i][j - limit - 1][0];
                }
                if (dp[i][j][1] < 1) { dp[i][j][1] += MODULO; }
                dp[i][j][1] %= MODULO;
            }
        }
        return (dp[zero][one][0] + dp[zero][one][1]) % MODULO;
    }
};

static void test(int zero, int one, int limit) {
    cout << Solution().numberOfStableArrays(zero, one, limit) << endl;
}

int main() {
    test(1, 1, 2);
    test(1, 2, 1);
    test(3, 3, 2);
    return 0;
}