#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>

using namespace std;
class Solution {
public:

    static vector<int> make_digits(long long value) {
        if (value == 0) { return { 0 }; }
        vector<int> digits;
        long long cur = value;
        while (cur > 0) {
            digits.emplace_back(cur % 10);
            cur /= 10;
        }
        return vector<int>(crbegin(digits), crend(digits));
    }

    static long long digitdp(long long value, int limit, const vector<int>& suffixes) {
        const auto digits = make_digits(value);
        const auto n = size(digits);
        if (n < size(suffixes)) {
            return 0LL;
        }
        if (n == size(suffixes)) {
            for (int i = 0; i < n; i++) {
                if (digits[i] > suffixes[i]) {
                    return 1LL;
                }
                if (digits[i] < suffixes[i]) {
                    return 0LL;
                }
            }
            return 1LL;
        }
        vector<vector<long long>> dp(n, vector<long long>(2));
        dp[0][1] = digits[0] <= limit ? 1LL : 0LL;
        dp[0][0] = min(digits[0] - 1, limit);
        const auto m = n - size(suffixes);
        for (int i = 1; i < m; i++) {
            dp[i][1] = digits[i] <= limit ? dp[i - 1][1] : 0;

            for (int j = 0; j <= min(limit, digits[i] - 1); j++) {
                dp[i][0] += dp[i - 1][1];
            }
            for (int j = 0; j <= limit; j++) {
                dp[i][0] += dp[i - 1][0];
            }
            for (int j = 1; j <= limit; j++) {
                dp[i][0] += 1LL;
            }
        }
        dp[m][0] += 1LL;
        for (int i = m; i < n; i++) {
            dp[i][1] = digits[i] == suffixes[i - m] ? dp[i - 1][1] : 0LL;
            if (suffixes[i - m] < digits[i]) {
                dp[i][0] += dp[i - 1][1];
            }
            dp[i][0] += dp[i - 1][0];
        }
        return dp[n - 1][0] + dp[n - 1][1];
    }


    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        vector<int> suffixes(size(s));
        for (int i = 0; i < size(s); i++) {
            suffixes[i] = static_cast<int>(s[i] - '0');
        }
        return digitdp(finish, limit, suffixes) - digitdp(start - 1, limit, suffixes);
    }
};

void test(long long start, long long finish, int limit, string&& s) {
    cout << Solution().numberOfPowerfulInt(start, finish, limit, s) << endl;
}
int main() {
    test(15, 215, 6, "10");
    test(1LL, 6000LL, 4, "124");
    test(1000, 2000, 4, "3000");
    return 0;
}