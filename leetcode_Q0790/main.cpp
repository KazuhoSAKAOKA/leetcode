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
constexpr long long MODULO = 1e9 + 7;
class Solution {
public:
    int numTilings(int n) {
        vector<long long> dp(n + 1);
        dp[0] = 1LL;
        dp[1] = dp[1 - 1];
        if (n > 1) {
            dp[2] = dp[2 - 1] + dp[2 - 2];
            if (n > 2) {
                for (int i = 3; i < n + 1; i++) {
                    dp[i] = dp[i - 1] + dp[i - 2];
                    dp[i] %= MODULO;
                    for (int j = 0; j < i - 2; j++) {
                        dp[i] += dp[j] * 2;
                        dp[i] %= MODULO;
                    }
                }
            }
        }
        return dp.back();
    }
};
void test(int n) {
    cout << Solution().numTilings(n) << endl;
}
int main() {
    test(4);//11
    test(5);//24
    test(6);//53
	return 0;
}