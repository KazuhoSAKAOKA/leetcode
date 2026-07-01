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

    static vector<long long> get_digits(long long n) {
        if (n == 0) { return { 0 }; }
        vector<long long> digits;
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
        return vector<long long>(crbegin(digits), crend(digits));
    }

    static long long digit_dp(long long v, long long k) {
        if (v < 10) {
            return v;
        }
        const auto digits = get_digits(v);
        const long long n = size(digits);
        vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(10, vector<long long>(2)));
        dp[0][digits[0]][1] = 1;
        for (long long d = 1; d < digits[0]; d++) {
            dp[0][d][0] = 1;
        }

        for (long long i = 1; i < n; i++) {
            for (long long d = 1; d < 10; d++) {
                dp[i][d][0] += 1;
            }

            if (abs(digits[i - 1] - digits[i]) <= k) {
                dp[i][digits[i]][1] = dp[i - 1][digits[i - 1]][1];
            }

            for (long long d = max(0LL, digits[i - 1] - k); d <= min(digits[i] - 1LL, min(digits[i - 1] + k, 9LL)); d++) {
                dp[i][d][0] += dp[i - 1][digits[i - 1]][1];
            }

            for (long long d = 0; d < 10; d++) {
                for (long long bd = max(0LL, d - k); bd <= min(d + k, 9LL); bd++) {
                    dp[i][d][0] += dp[i - 1][bd][0];
                }
            }
        }
        long long result = 0;
        for (long long d = 0; d < 10; d++) {
            result += dp[n - 1][d][0] + dp[n - 1][d][1];
        }
        return result;
    }

    long long goodIntegers(long long l, long long r, int k) {
        const auto lval = digit_dp(l - 1, k);
        const auto rval = digit_dp(r, k);
        return rval - lval;
    }
};

static void test(long long l, long long r, int k) {
    cout << Solution().goodIntegers(l, r, k) << endl;
}

int main() {
    test(10, 15, 1);
    test(201, 204, 2);
    return 0;
}
