#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include <unordered_map>

using namespace std;
class Solution {
public:

    static vector<int> get_digits(int n) {
        if (n == 0) { return { 0 }; }
        vector<int> digits;
        int cur(n);
        while (cur > 0) {
            digits.emplace_back(cur % 10);
            cur /= 10;
        }

        return vector<int>(crbegin(digits), crend(digits));
    }

    int countLargestGroup(int n) {
        const auto digits = get_digits(n);
        const auto len = size(digits);
        vector<vector<unordered_map<int, int>>> dp(len, vector<unordered_map<int, int>>(2));
        dp[0][1][digits[0]] = 1;
        for (int i = 1; i < digits[0]; i++) {
            dp[0][0][i] = 1;
        }
        for (int i = 1; i < len; i++) {
            for (auto&& [d, count] : dp[i - 1][1]) {
                dp[i][1][d + digits[i]] = count;
                for (int j = 0; j < digits[i]; j++) {
                    dp[i][0][d + j] += count;
                }
            }
            for (auto&& [d, count] : dp[i - 1][0]) {
                for (int j = 0; j <= 9; j++) {
                    dp[i][0][j + d] += count;
                }
            }
            for (int j = 1; j <= 9; j++) {
                dp[i][0][j] += 1;
            }
        }
        map<int, int> temp_map;


        for (auto&& [s, count] : dp[len - 1][0]) {
            temp_map[s] += count;
        }
        for (auto&& [s, count] : dp[len - 1][1]) {
            temp_map[s] += count;
        }
        int max_size = INT_MIN;
        int max_size_count = 0;
        for (auto&& [s, count] : temp_map) {
            if (max_size < count) {
                max_size = count;
                max_size_count = 1;
            }
            else if (max_size == count) {
                max_size_count++;
            }
        }
        return max_size_count;
    }
};
void test(int n) {
    cout << Solution().countLargestGroup(n) << endl;
}
int main() {
    test(24);
    test(13);
    test(2);
	return 0;
}