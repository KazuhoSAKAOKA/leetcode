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
    int colorTheGrid(int m, int n) {
        constexpr long long MODULO = 1e9 + 7;
        constexpr long long COLORS = 3;
        constexpr long long MAXBITMASK = (1 << (3 * 5));
        vector<unordered_map<int, long long>> dp(n);
        dp[0][1 << 0] = 1;
        dp[0][1 << 1] = 1;
        dp[0][1 << 2] = 1;
        for (int j = 1; j < m; j++) {
            dp[0][(1 << ((j * 3) + 0))] = (dp[0][(1 << (((j - 1) * 3) + 1))] + dp[0][(1 << (((j - 1) * 3) + 2))]) % MODULO;
            dp[0][(1 << ((j * 3) + 1))] = (dp[0][(1 << (((j - 1) * 3) + 0))] + dp[0][(1 << (((j - 1) * 3) + 2))]) % MODULO;
            dp[0][(1 << ((j * 3) + 2))] = (dp[0][(1 << (((j - 1) * 3) + 0))] + dp[0][(1 << (((j - 1) * 3) + 1))]) % MODULO;
        }

        for (int i = 1; i < n; i++) {
            dp[i][(1 << ((0 * 3) + 0))] = (dp[i - 1][(1 << ((0 * 3) + 1))] + dp[i - 1][(1 << (((0 * 3) * 3) + 2))]) % MODULO;
            dp[i][(1 << ((0 * 3) + 1))] = (dp[i - 1][(1 << ((0 * 3) + 0))] + dp[i - 1][(1 << (((0 * 3) * 3) + 2))]) % MODULO;
            dp[i][(1 << ((0 * 3) + 2))] = (dp[i - 1][(1 << ((0 * 3) + 0))] + dp[i - 1][(1 << (((0 * 3) * 3) + 1))]) % MODULO;


            for (int j = 1; j < m; j++) {
                for (int k = 0; k < 3; k++) {
                    long long v = 0;
                    const auto left_upper_mask = 1 << ((j - 1) * 3 + k);
                    const auto left_same_mask = 1 << (j * 3 + k);
                    for (auto&& [mask, value] : dp[i - 1]) {
                        if (mask & left_upper_mask) {
                            v += value;
                            v %= MODULO;
                        }
                        else {
                            if ((mask & left_same_mask) == 0) {
                                v += value;
                                v %= MODULO;
                            }
                        }
                    }
                    dp[i][(1 << ((j * 3) + k))] = v;
                }
            }
        }

        long long total = 0;
        for (int i = 0; i < MAXBITMASK; i++) {
            total += dp.back()[i];
            total %= MODULO;
        }
        return static_cast<int>(total);
    }

    static void create_rec(int m, int index, const vector<char>& colors, string& cur, vector<string>& list) {
        if (index == m) {
            list.emplace_back(cur);
            return;
        }
        for (auto&& c : colors) {
            if (cur.empty() || cur.back() != c) {
                cur += c;
                create_rec(m, index + 1, colors, cur, list);
                cur.pop_back();
            }
        }
    }
    static bool valid(const string& a, const string& b) {
        for (int i = 0; i < size(a); i++) {
            if (a[i] == b[i]) {
                return false;
            }
        }
        return true;
    }
    int colorTheGrid1(int m, int n) {
        constexpr long long MODULO = 1e9 + 7;
        vector<unordered_map<string, long long>> dp(n);
        const vector<char> colors{ 'R','G', 'B' };
        vector<string> list;
        string work;
        create_rec(m, 0, colors, work, list);
        for (auto&& state : list) {
            dp[0].insert({ state, 1 });
        }

        for (int i = 1; i < n; i++) {
            for (auto&& [before_state, count] : dp[i - 1]) {
                for (auto&& cur_state : list) {
                    if (valid(before_state, cur_state)) {
                        auto it = dp[i].find(cur_state);
                        if (it == cend(dp[i])) {
                            dp[i].insert({cur_state, count});
                        }
                        else {
                            it->second += count;
                            it->second %= MODULO;
                        }
                    }
                }
            }
        }

        long long total = 0;
        for (auto&& [_, count] : dp.back()) {
            total += count;
            total %= MODULO;
        }
        return static_cast<int>(total);
    }

};

void test(int m, int n) {
    cout << Solution().colorTheGrid1(m, n) << endl;
}
int main() {
    test(2, 2);
    test(1, 1);
    test(1, 2);
    test(5, 5);
	return 0;
}