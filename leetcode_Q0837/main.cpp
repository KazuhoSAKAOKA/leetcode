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

    static double tle(int n, int k, int maxPts) {
        vector<vector<double>> dp(k + 1, vector<double>(k + 1, 0.0));
        dp[0][0] = 1.0;
        double overrate = 0.0;
        const double ratio = 1.0 / maxPts;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (dp[i][j] == 0.0) { continue; }
                const auto max_val = j + maxPts;
                const auto lim = min(k, max_val);
                for (int l = j + 1; l <= lim; l++) {
                    dp[i + 1][l] += dp[i][j] * ratio;
                }
                if (n < max_val) {
                    overrate += (max_val - n) * dp[i][j] * ratio;
                }
            }
        }
        return 1.0 - overrate;
    }


    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k + maxPts) {
            return 1.0;
        }
        vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;
        double windowSum = 1.0, result = 0.0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = windowSum / maxPts;
            if (i < k) { 
                windowSum += dp[i]; 
            }
            else {
                result += dp[i];
            }
            if (i - maxPts >= 0) {
                windowSum -= dp[i - maxPts];
            }
        }
        return result;
    }
};
static void test(int n, int k, int maxPts) {
    cout << Solution().new21Game(n, k, maxPts) << endl;
}
int main() {
    test(21, 17, 10);
    test(10, 1, 10);
    test(6, 1, 10);
	return 0;
}