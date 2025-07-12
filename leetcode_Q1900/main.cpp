#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <numeric>
#include <climits>
#include <cmath>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:
    using memo_key_t = int;
    using memo_t = map<memo_key_t, pair<int, int>>;

    static int get_next_head(int current, int n, int bits) {
        int bit = current;
        while (bit < n && ((1 << bit) & bits) == 0) {
            bit++;
        }
        return bit;
    }
    static int get_next_tail(int current, int bits) {
        int bit = current;
        while (bit >= 0 && ((1 << bit) & bits) == 0) {
            bit--;
        }
        return bit;
    }

    static pair<int, int> rec(int n, int firstPlayer, int secondPlayer, int round, int remain_bits, memo_t& memo) {

        const auto key = remain_bits;
        const auto it = memo.find(key);
        if (it != cend(memo)) {
            return it->second;
        }

        int i = 0;
        int j = n - 1;
        vector<pair<int, int>> pairs;
        while (i < j) {
            i = get_next_head(i, n, remain_bits);
            j = get_next_tail(j, remain_bits);
            if (i < j) {
                if (i + 1 == firstPlayer && j + 1 == secondPlayer) {
                    return memo[key] = { round,round };
                }
                else {
                    pairs.emplace_back(make_pair(i, j));
                }
            }
            i++;
            j--;
        }

        if (pairs.empty()) {
            cerr << "invalid" << endl;
        }


        int min_value = INT_MAX;
        int max_value = 0;
        int masks = (1 << size(pairs)) - 1;
        for (int mask = 0; mask <= masks; mask++) {
            int cur_bits(remain_bits);
            for (int j = 0; j < size(pairs); j++) {
                auto&& [left, right] = pairs[j];
                if ((mask & (1 << j)) == 0) {
                    //left勝ち
                    if (right + 1 == firstPlayer || right + 1 == secondPlayer) {
                        cur_bits = 0;
                        break;
                    }
                    cur_bits &= ~(1 << right);
                }
                else {
                    //right勝ち
                    if (left + 1 == firstPlayer || left + 1 == secondPlayer) {
                        cur_bits = 0;
                        break;
                    }
                    cur_bits &= ~(1 << left);
                }
            }
            if (cur_bits != 0) {
                const auto [min1, max1] = rec(n, firstPlayer, secondPlayer, round + 1, cur_bits, memo);
                min_value = min(min_value, min1);
                max_value = max(max_value, max1);
            }
        }
        return memo[key] = { min_value, max_value };
    }


    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        int bits = (1 << n) - 1;
        memo_t memo;
        const auto [mina, maxa] = rec(n, firstPlayer, secondPlayer, 1, bits, memo);
        return { mina, maxa };
    }
};

static void test(int n, int firstPlayer, int secondPlayer) {
    output(Solution().earliestAndLatest(n, firstPlayer, secondPlayer));
}
int main() {
    test(11, 2, 4);
    test(5, 1, 5);
    return 0;
}