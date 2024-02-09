// leetcode_Q0279.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <algorithm>
using namespace std;

class Solution {
public:

    using memo_key_type = pair<int, int>;
    using memo_type = map<memo_key_type, optional<int>>;

    optional<int> rec(const vector<int>& ps, int index, int remain, memo_type& memo) {
        if (remain == 0) {
            return 0;
        }
        if (remain < 0) {
            return nullopt;
        }
        if (index == ps.size()) {
            return nullopt;
        }
        if (index == ps.size() - 1) {
            return remain;
        }

        const auto key = memo_key_type(index, remain);
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }
        optional<int> min_count = nullopt;
        int n = 0;
        while (n * ps[index] <= remain) {
            const auto ret = rec(ps, index + 1, remain - n * ps[index], memo);
            if (ret.has_value()){
                if (min_count.has_value()) {
                    min_count = min(min_count.value(), ret.value() + n);
                }
                else {
                    min_count = ret.value() + n;
                }
            }
            n++;
        }
        memo[key] = min_count;
        return min_count;
    }

    int tle(int n) {
        vector<int> ps;

        int base = 1;
        for (;;) {
            int v = base * base;
            if (n < v) {
                break;
            }
            ps.emplace_back(v);
            base++;
        }
        sort(begin(ps), end(ps), [](const auto& a, const auto& b) { return b < a; });
        memo_type memo;
        return rec(ps, 0, n, memo).value_or(0);
    }


    int numSquares(int n) {
        vector<int> dp(n + 1, 0);

        vector<int> ps;

        int base = 1;
        for (;;) {
            int v = base * base;
            if (n < v) {
                break;
            }
            ps.emplace_back(v);
            base++;
        }

        for (int i = 1; i <= n; i++) {
            int min_value = i;
            for (int j = 0; j < ps.size(); j++) {
                if (i < ps[j]) {
                    break;
                }
                min_value = min(min_value, dp[i - ps[j]] + 1);
            }
            dp[i] = min_value;
        }
        return dp[n];
    }
};

void test(int n) {
    cout << Solution().numSquares(n) << endl;
}

int main()
{
    test(6175);
    test(6665);
    test(12);
    test(13);
}