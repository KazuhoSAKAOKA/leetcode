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

    static vector<int> get_digits(int num) {
        if (num == 0) { return{ 0 }; }
        vector<int> digits;

        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }

        return vector<int>(crbegin(digits), crend(digits));
    }
    static long long digit_dp(int num) {
        if (num < 100) { return 0LL; }
        const auto digits = get_digits(num);
        const auto n = size(digits);
        constexpr size_t valley = 0;
        constexpr size_t flat = 1;
        constexpr size_t peak = 2;
        //dp[column][digit][upper,other,lower][eq]
        vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(10, vector<vector<int>>(3, vector<int>(2))));
        dp[0][digits[0]][flat][1] = 1;
        for (int d = 1; d < digits[0]; d++) {
            dp[0][d][flat][0] = 1;
        }

        long long result = 0LL;
        for (size_t i = 1; i < n; i++) {

            //eq
            if (digits[i - 1] < digits[i]) {
                result += dp[i - 1][digits[i - 1]][valley][1];
                dp[i][digits[i]][peak][1] = dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
            }
            else if (digits[i - 1] > digits[i]) {
                result += dp[i - 1][digits[i - 1]][peak][1];
                dp[i][digits[i]][valley][1] = dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
            }
            else {
                //digits[i - 1] == digits[i]
                dp[i][digits[i]][flat][1] = dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
            }

            //eq->low
            for (int d = 0; d < digits[i]; d++) {
                if (digits[i - 1] < d) {
                    result += dp[i - 1][digits[i - 1]][valley][1];
                    dp[i][d][peak][0] += dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
                }
                else if (digits[i - 1] > d) {
                    result += dp[i - 1][digits[i - 1]][peak][1];
                    dp[i][d][valley][0] += dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
                }
                else {
                    dp[i][d][flat][0] += dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
                }
            }

            //low
            for (int d = 0; d < 10; d++) {
                if (d != 0) {
                    dp[i][d][flat][0] += 1;
                }
                dp[i][d][flat][0] += dp[i - 1][d][0][0] + dp[i - 1][d][1][0] + dp[i - 1][d][2][0];

                for (int bd = 0; bd < d; bd++) {
                    result += dp[i - 1][bd][valley][0];
                    dp[i][d][peak][0] += dp[i - 1][bd][0][0] + dp[i - 1][bd][1][0] + dp[i - 1][bd][2][0];
                }
                for (int bd = d + 1; bd < 10; bd++) {
                    result += dp[i - 1][bd][peak][0];
                    dp[i][d][valley][0] += dp[i - 1][bd][0][0] + dp[i - 1][bd][1][0] + dp[i - 1][bd][2][0];
                }
            }

        }
        return result;
    }

    int totalWaviness(int num1, int num2) {
        int ans = 0;
        for (int i = num1; i <= num2; i++) {
            auto digits = get_digits(i);
            for (int i = 1; i < size(digits) - 1; i++) {
                if (
                    (digits[i - 1] < digits[i] && digits[i] > digits[i + 1]) ||
                    (digits[i - 1] > digits[i] && digits[i] < digits[i + 1])) {
                    ans++;
                }
            }
        }
        return ans;
    }
};

static void test(int num1, int num2) {
    cout << Solution().totalWaviness(num1, num2) << endl;
}


int main() {
    test(1, 1011);
    //test(120, 130);
    //test(198, 202);
    //test(4848, 4848);
    //test(0, 121);
    return 0;
}
