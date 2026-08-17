#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <numbers>
#include <cmath>
#include <climits>
#include <tuple>
#include <functional>
#include <bit>
#include <exception>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    static long long rec(const vector<long long>& prefix_sums, int b, int e, vector<vector<long long>>& memo) {
        if (e - b <= 1) {
            return 0LL;
        }
        const auto key = make_pair(b, e);
        if (0 <= memo[b][e]) {
            return memo[b][e];
        }
        long long best_score = 0LL;

        for (int i = b + 1; i < e; i++) {
            const auto l_score = prefix_sums[i] - prefix_sums[b];
            const auto r_score = prefix_sums[e] - prefix_sums[i];
            long long cur_score = 0LL;
            if (l_score == r_score) {
                const auto score1 = rec(prefix_sums, b, i, memo);
                const auto score2 = rec(prefix_sums, i, e, memo);
                cur_score = l_score + max(score1, score2);
            }
            else {
                if (l_score < r_score) {
                    cur_score = l_score + rec(prefix_sums, b, i, memo);
                }
                else {
                    cur_score = r_score + rec(prefix_sums, i, e, memo);
                }
            }
            best_score = max(best_score, cur_score);
        }
        memo[b][e] = best_score;
        return best_score;
    }

    int stoneGameV(vector<int>& stoneValue) {
        const auto n = size(stoneValue);
        if (n == 1) { return 0; }
        vector<long long> prefix_sums(n + 1);
        for (size_t i = 0; i < n; i++) {
            prefix_sums[i + 1] = prefix_sums[i] + stoneValue[i];
        }
        vector<vector<long long>> memo(n + 1, vector<long long>(n + 1, -1));
        return static_cast<int>(rec(prefix_sums, 0, n, memo));
    }
};


static void test(vector<int>&& stones) {
    cout << Solution().stoneGameV(stones) << endl;
}

int main() {
    test(get_list_int("[6,2,3,4,5,5]"));
    test(get_list_int("[7,7,7,7,7,7,7]"));
    test(get_list_int("[5,1,2,4,3]"));
    return 0;
}