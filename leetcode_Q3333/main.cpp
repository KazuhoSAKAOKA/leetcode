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

    static int mle(const string& word, int k) {
        constexpr long long MODULO = 1e9 + 7;
        const int n = size(word);
        const int remain = n - k;

        vector<int> dups;
        int cur_streak = 1;
        for (int i = 1; i < n; i++) {
            if (word[i - 1] != word[i]) {
                if (cur_streak > 1) {
                    dups.emplace_back(cur_streak);
                }
                cur_streak = 1;
            }
            else {
                cur_streak++;
            }
        }
        if (cur_streak > 1) {
            dups.emplace_back(cur_streak);
            cur_streak = 1;
        }
        const int m = size(dups);
        vector<vector<long long>> dp(m + 1, vector<long long>(remain + 1));
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            int j = 0;
            while (j <= remain && dp[i][j] > 0) {
                for (int l = j; l <= min(remain, j + dups[i] - 1); l++) {
                    dp[i + 1][l] += dp[i][j];
                    dp[i + 1][l] %= MODULO;
                }
                j++;
            }
        }

        long long count = 0;
        for (auto&& v : dp.back()) {
            count += v;
            count %= MODULO;
        }
        return static_cast<int>(count);
    }

    int possibleStringCount(string word, int k) {
        constexpr long long MODULO = 1e9 + 7;
        const int n = size(word);
        vector<long long> dups;
        int cur_streak = 1;
        int groups = 0;
        for (int i = 1; i < n; i++) {
            if (word[i - 1] != word[i]) {
                if (cur_streak > 1) {
                    dups.emplace_back(cur_streak - 1);
                }
                cur_streak = 1;
                groups++;
            }
            else {
                cur_streak++;
            }
        }
        if (cur_streak > 1) {
            dups.emplace_back(cur_streak - 1);
            cur_streak = 1;
        }
        groups++;

        const long long m = size(dups);
        if (m == 0) {
            return 1;
        }
        const long long cnt = k - groups;
        if (cnt <= 0) {
            return accumulate(cbegin(dups), cend(dups), 1LL, [](long long a, long long b) { return a * (b + 1) % MODULO; });
        }        
        vector<long long> prev(cnt);
        prev[0] = 1;

        long long total = 1;
        for (long long i = 0; i < m; i++) {
            total *= (dups[i] + 1);
            total %= MODULO;
            vector<long long> current(cnt);
            vector<long long> diffs(cnt + 1);
            for (long long j = 0; j < cnt; j++) {
                diffs[j] += (prev[j]);
                const auto index = min(cnt, j + dups[i] + 1);
                diffs[index] -= (prev[j]);
                if (diffs[index] < 0) {
                    diffs[index] += MODULO;
                }
            }
            long long cur_value = 0;
            for (long long j = 0; j < cnt; j++) {
                cur_value += MODULO + diffs[j];
                cur_value %= MODULO;
                current[j] = cur_value;
            }
            swap(current, prev);
        }

        long long count = 0;
        for (auto&& p :prev) {
            count += p;
            count %= MODULO;
        }
        return ((total + MODULO) - static_cast<int>(count)) % MODULO;
    }
};

static void test(string&& word, int k) {
    cout << Solution().possibleStringCount(word, k) << endl;
}
int main() {
    test("bb", 1);
    test("d", 1);
    test("aaabbb", 3);
    test("aabbccdd", 7);
    test("aabbccdd", 8);
    return 0;
}