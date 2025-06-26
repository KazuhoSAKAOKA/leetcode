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

    static int tle(string&& s, int k) {
        const auto n = size(s);
        vector<unordered_map<int, int>> dp(n + 1);
        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            const auto cur = s[i] == '1' ? 1 : 0;
            auto& cur_map = dp[i + 1];
            for (auto&& [v, len] : dp[i]) {
                cur_map[v] = max(cur_map[v], len);
                const auto v1 = v << 1 | cur;
                if (v1 <= k) {
                    cur_map[v1] = max(cur_map[v1], len + 1);
                }
            }
        }
        int max_len = 0;
        for (auto&& [_, len] : dp.back()) {
            max_len = max(max_len, len);
        }
        return max_len;
    }

    int longestSubsequence(string s, int k) {
        int cur_value = 0;
        auto it = crbegin(s);
        int len = 0;
        while (it != crend(s) && cur_value <= k && len < 31) {
            if (*it == '1') {
                cur_value |= (1 << len);
            }
            if (k < cur_value) {
                break;
            }
            ++it;
            len++;
        }
        const int zeros = count_if(it, crend(s), [](char c) { return c == '0'; });
        return len + zeros;
    }
};
void test(string&& s, int k) {
    cout << Solution().longestSubsequence(s, k) << endl;
}
int main() {
    test("1001010", 5);
    test("00101001", 1);
    return 0;
}