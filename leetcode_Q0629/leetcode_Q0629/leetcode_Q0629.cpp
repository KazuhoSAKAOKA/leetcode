// leetcode_Q0629.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <set>
#include <numeric>

using namespace std;

class Solution {
public:

    static bool is_k_inverse_pairs(int k, const vector<int>& current) {
        int count = 0;
        for (int i = 0; i < current.size() - 1;i++) {
            for (int j = i + 1; j < current.size(); j++) {
                if (current[j] < current[i]) {
                    count++;
                }
            }
        }
        return count == k;
    }
    static int rec(int n, int k, set<int>& remain, vector<int>& current) {
        if (n == current.size()) {
            return is_k_inverse_pairs(k, current) ? 1 : 0;
        }

        int64_t count = 0;

        auto copyset(remain);
        for (auto&& value : remain) {
            current.emplace_back(value);
            copyset.erase(value);
            count += rec(n, k, copyset, current);
            count %= MODULO;
            copyset.insert(value);
            current.pop_back();
        }

        return static_cast<int>(count);
    }

    static int callrec(int n, int k) {
        set<int> remain;

        vector<int> current;
        for (int i = 0; i < n; i++) {
            remain.insert(i + 1);
        }
        return rec(n, k, remain, current);

    }

    static int rec2(int n, int k, set<int>& remain, vector<int>& current, int current_pair_count) {
        if (n == current.size()) {
            return k == current_pair_count ? 1 : 0;
        }

        int64_t count = 0;

        auto copyset(remain);
        for (auto&& value : remain) {
            int add_pair_count = accumulate(cbegin(current), cend(current), 0, [value](const auto b, const auto& x) { return b + (value < x ? 1 : 0);  });
            if (k < add_pair_count + current_pair_count) { continue; }
            current.emplace_back(value);
            copyset.erase(value);
            count += rec2(n, k, copyset, current, current_pair_count + add_pair_count);
            count %= MODULO;
            copyset.insert(value);
            current.pop_back();
        }

        return static_cast<int>(count);
    }

    static int rec3(int n, int k, vector<vector<int>>& memo) {
        if (n == 0) {
            return 0;
        }
        if (k == 0) {
            return 1;
        }

        if (memo[n][k] != 0) {
            return memo[n][k];
        }

        int64_t count = 0;

        for (int i = 0; i <= min(k, n - 1); i++) {
            count += rec3(n - 1, k - i, memo);
            count %= MODULO;
        }
        memo[n][k] = static_cast<int>(count);
        return memo[n][k];
    }

    static const int64_t MODULO = 1000000000 + 7;

    int kInversePairs(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    int c = 0;
                    for (int p = 0; p <= min(j, i - 1); p++) {
                        c = (c + dp[i - 1][j - p]) % MODULO;
                    }
                    dp[i][j] = c;
                }
            }
        }
        return dp[n][k];
    }
};

void test(int n, int k) {
    cout << Solution().kInversePairs(n, k) << endl;
}

int main()
{
    test(1000, 1000);
    test(10, 11);

    test(3, 0);
    test(3, 1);
}
