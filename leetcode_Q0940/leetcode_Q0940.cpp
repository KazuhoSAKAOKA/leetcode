// leetcode_Q0940.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        constexpr long long MODULO = 1e9 + 7;
        const auto n = size(s);

        vector<long long> dp(n + 1);
        dp[0] = 1;
        vector<size_t> last_index(26, -1);

        for (size_t i = 0; i < n; i++) {
            dp[i + 1] = dp[i] * 2;
            dp[i + 1] %= MODULO;
            const auto char_index = s[i] - 'a';
            if (last_index[char_index] <= n) {
                dp[i + 1] += MODULO - dp[last_index[char_index]];
                dp[i + 1] %= MODULO;
            }
            last_index[char_index] = i;
        }

        long long ans = (dp.back() - dp[0] + MODULO) % MODULO;
        return static_cast<int>(ans);
    }
};

static void test(string&& s) {
    cout << Solution().distinctSubseqII(s) << endl;
}

int main() {
    test("abc");
    test("aba");
    test("aaa");

    return 0;
}
