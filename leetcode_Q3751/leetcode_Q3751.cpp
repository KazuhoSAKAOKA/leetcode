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

    static vector<long long> get_digits(long long num) {
        if (num == 0) { return{ 0 }; }
        vector<long long> digits;

        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }

        return vector<long long>(crbegin(digits), crend(digits));
    }


    static size_t digit_dp(long long num) {
        if (num < 100) { return 0LL; }
        const auto digits = get_digits(num);
        const auto n = size(digits);
        constexpr size_t valley = 0;
        constexpr size_t flat = 1;
        constexpr size_t peak = 2;
        //dp[column][digit][upper,other,lower][eq]
        vector<vector<vector<vector<long long>>>> dp(n, vector<vector<vector<long long>>>(10, vector<vector<long long>>(3, vector<long long>(2))));
        vector<vector<vector<vector<size_t>>>> dp_result(n, vector<vector<vector<size_t>>>(10, vector<vector<size_t>>(3, vector<size_t>(2))));
        dp[0][digits[0]][flat][1] = 1;
        for (int d = 1; d < digits[0]; d++) {
            dp[0][d][flat][0] = 1;
        }

        for (size_t i = 1; i < n; i++) {
            //eq
            if (digits[i - 1] < digits[i]) {
                dp_result[i][digits[i]][peak][1] += (dp[i - 1][digits[i - 1]][valley][1]);
                dp[i][digits[i]][peak][1] = dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
            }
            else if (digits[i - 1] > digits[i]) {
                dp_result[i][digits[i]][valley][1] += (dp[i - 1][digits[i - 1]][peak][1]);
                dp[i][digits[i]][valley][1] = dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
            }
            else {
                //digits[i - 1] == digits[i]
                dp[i][digits[i]][flat][1] = dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
            }
            for (int s = 0; s < 3; s++) {
                dp_result[i][digits[i]][s][1] += dp_result[i - 1][digits[i - 1]][s][1];
            }
            for (int d = 0; d < digits[i]; d++) {
                for (int s = 0; s < 3; s++) {
                    dp_result[i][d][s][0] += dp_result[i - 1][digits[i - 1]][s][1];
                }
            }
            //eq->low
            for (size_t d = 0; d < digits[i]; d++) {
                if (digits[i - 1] < d) {
                    dp_result[i][d][peak][0] += (dp[i - 1][digits[i - 1]][valley][1]);
                    dp[i][d][peak][0] += dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
                }
                else if (digits[i - 1] > d) {
                    dp_result[i][d][valley][0] += (dp[i - 1][digits[i - 1]][peak][1]);
                    dp[i][d][valley][0] += dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
                }
                else {
                    dp[i][d][flat][0] += dp[i - 1][digits[i - 1]][0][1] + dp[i - 1][digits[i - 1]][1][1] + dp[i - 1][digits[i - 1]][2][1];
                }
            }

            //low
            for (size_t d = 0; d < 10; d++) {
                if (d != 0) {
                    dp[i][d][flat][0] += 1;
                }
                dp[i][d][flat][0] += dp[i - 1][d][0][0] + dp[i - 1][d][1][0] + dp[i - 1][d][2][0];

                for (size_t bd = 0; bd < d; bd++) {
                    dp_result[i][d][peak][0] += (dp[i - 1][bd][valley][0]);
                    dp[i][d][peak][0] += dp[i - 1][bd][0][0] + dp[i - 1][bd][1][0] + dp[i - 1][bd][2][0];
                }
                for (size_t bd = d + 1; bd < 10; bd++) {
                    dp_result[i][d][valley][0] += (dp[i - 1][bd][peak][0]);
                    dp[i][d][valley][0] += dp[i - 1][bd][0][0] + dp[i - 1][bd][1][0] + dp[i - 1][bd][2][0];
                }
            }


            for (size_t db = 0; db < 10; db++) {
                for (int d = 0; d < 10; d++) {
                    for (int s = 0; s < 3; s++) {
                        dp_result[i][d][s][0] += dp_result[i - 1][db][s][0];
                    }
                }
            }
        }

        size_t result = 0;
        for (int d = 0; d < 10; d++) {
            for (int s = 0; s < 3; s++) {
                result += dp_result.back()[d][s][0] + dp_result.back()[d][s][1];
            }
        }

        return result;
    }

    long long totalWaviness(long long num1, long long num2) {
        const auto v1 = digit_dp(num1 - 1);
        const auto v2 = digit_dp(num2);
        const auto result = v2 - v1;

        return result;
    }
};

static void test(int num1, int num2) {
    cout << Solution().totalWaviness(num1, num2) << endl;
}


int main() {
    test(2549294942, 5067104447);
    //test(1, 1011);
    //test(120, 130);
    //test(198, 202);
    //test(4848, 4848);
    //test(0, 121);
    return 0;
}
