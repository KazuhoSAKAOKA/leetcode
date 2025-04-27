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

    static int mle(int n, int maxValue) {
        constexpr long long MODULO = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(maxValue));
        for (int j = 0; j < maxValue; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < maxValue; j++) {
                int k = j + 1;
                while (k <= maxValue) {
                    dp[i][k - 1] += dp[i - 1][j];
                    dp[i][k - 1] %= MODULO;
                    k += (j + 1);
                }
            }
        }
        long long count = 0;
        for (int j = 0; j < maxValue; j++) {
            count += dp[n - 1][j];
            count %= MODULO;
        }
        return static_cast<int>(count);
    }


    int idealArrays(int n, int maxValue) {
        constexpr long long MODULO = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(maxValue));
        for (int j = 0; j < maxValue; j++) {
            dp[0][j] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < maxValue; j++) {
                int k = j + 1;
                while (k <= maxValue) {
                    dp[i][k - 1] += dp[i - 1][j];
                    dp[i][k - 1] %= MODULO;
                    k += (j + 1);
                }
            }
        }
        long long count = 0;
        for (int j = 0; j < maxValue; j++) {
            count += dp[n - 1][j];
            count %= MODULO;
        }
        return static_cast<int>(count);
    }
};

void test(int n, int maxValue) {
    cout << Solution().idealArrays(n, maxValue) << endl;
}
int main() {
    test(2, 5);
    test(5, 3);
	return 0;
}