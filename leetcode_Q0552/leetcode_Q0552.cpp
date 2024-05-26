// leetcode_Q0552.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


class Solution {
public:

    using memo_key_t = tuple<int, int, bool>;
    using memo_t = map<memo_key_t, long long>;

    static int rec(int n, int index, int continue_late, bool absented, memo_t& memo) {
        if (n == index) {
            return 1;
        }

        const auto key = memo_key_t(index, continue_late, absented);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        long long value = 0;
        // P
        value += rec(n, index + 1, 0, absented, memo);
        value %= MODULO;
        // L
        if (continue_late < 2) {
            value += rec(n, index + 1, continue_late + 1, absented, memo);
            value %= MODULO;
        }

        // A
        if (!absented) {
            value += rec(n, index + 1, 0, true, memo);
            value %= MODULO;
        }

        memo[key] = value;

        return value;
    }
    static constexpr long long MODULO = 1000000007;

    int checkRecord(int n) {
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(3, vector<long long>(2, 0)));

        dp[0][0][0] = 1;

        for (int i = 0; i < n; i++) {
            const int index = i + 1;

            dp[index][0][0] = dp[i][0][0] + dp[i][1][0];
            dp[index][0][0] %= MODULO;
            dp[index][0][0] += dp[i][2][0];
            dp[index][0][0] %= MODULO;

            dp[index][0][1] = dp[i][0][1] + dp[i][1][1];
            dp[index][0][1] %= MODULO;
            dp[index][0][1] += dp[i][2][1];
            dp[index][0][1] %= MODULO;
            dp[index][0][1] += dp[i][0][0];
            dp[index][0][1] %= MODULO;
            dp[index][0][1] += dp[i][1][0];
            dp[index][0][1] %= MODULO;
            dp[index][0][1] += dp[i][2][0];
            dp[index][0][1] %= MODULO;

            dp[index][1][0] = dp[i][0][0];
            dp[index][1][0] %= MODULO;
            dp[index][2][0] = dp[i][1][0];
            dp[index][2][0] %= MODULO;

            dp[index][1][1] = dp[i][0][1];
            dp[index][1][1] %= MODULO;
            dp[index][2][1] = dp[i][1][1];
            dp[index][2][1] %= MODULO;
        }
        int ans = dp[n][0][0];
        ans += dp[n][0][1];
        ans %= MODULO;
        ans += dp[n][1][0];
        ans %= MODULO;
        ans += dp[n][2][0];
        ans %= MODULO;

        ans += dp[n][1][1];
        ans %= MODULO;
        ans += dp[n][2][1];
        ans %= MODULO;

        return ans;
    }
};

void test(int n) {
    cout << Solution().checkRecord(n) << endl;
}
int main()
{
    test(2);
    test(1);
    test(10101);
}
