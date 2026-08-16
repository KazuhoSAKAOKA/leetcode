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

    static int rec(const vector<int>& stones, int turn, vector<bool>& used, long long removed_sum) {

        if (removed_sum != 0 && removed_sum % 3 == 0) {
            return turn % 2 == 0 ? 1 : -1;
        }
        if (turn == size(stones)) {
            return -1;
        }

        const int win_value = turn % 2 == 0 ? 1 : -1;
        const int lose_value = turn % 2 == 0 ? -1 : 1;

        for (size_t i = 0; i < size(stones); i++) {
            if (!used[i]) {
                used[i] = true;
                const auto r = rec(stones, turn + 1, used, removed_sum + stones[i]);
                used[i] = false;
                if (win_value == r) {
                    return win_value;
                }
            }
        }
        return lose_value;
    }

    static bool tle(vector<int>& stones) {
        const auto n = size(stones);
        vector<bool> used(n);
        const auto r = rec(stones, 0, used, 0LL);
        return r > 0;
    }


    static int rec2(const vector<int>& stones_freq, int turn, vector<int>& used_count, int removed_sum, vector<map<tuple<int, int, int>, int>>& memo) {

        if (turn > 0 && removed_sum % 3 == 0) {
            return turn % 2 == 0 ? 1 : -1;
        }
        if (turn == stones_freq[0] + stones_freq[1] + stones_freq[2]) {
            return -1;
        }

        const auto key = make_tuple(used_count[0], used_count[1], used_count[2]);
        auto it = memo[turn].find(key);
        if (it != cend(memo[turn])) {
            return it->second;
        }

        const int win_value = turn % 2 == 0 ? 1 : -1;
        const int lose_value = turn % 2 == 0 ? -1 : 1;

        for (size_t i = 0; i < 3; i++) {
            if (stones_freq[i] - used_count[i] > 0) {
                used_count[i]++;
                const auto r = rec2(stones_freq, turn + 1, used_count, (removed_sum + i) % 3, memo);
                used_count[i]--;
                if (win_value == r) {
                    memo[turn].insert({ key, win_value });
                    return win_value;
                }
            }
        }
        memo[turn].insert({ key, lose_value });

        return lose_value;
    }
    static bool tle2(vector<int>& stones) {
        const auto n = size(stones);
        vector<int> stones_freq(3, 0);
        for (auto&& stone : stones) {
            stones_freq[stone % 3]++;
        }
        vector<int> used_count(3, 0);
        vector<map<tuple<int, int, int>, int>> memo(n);
        const auto r = rec2(stones_freq, 0, used_count, 0LL, memo);
        return r > 0;
    }


    bool stoneGameIX(vector<int>& stones) {
        const auto n = size(stones);
        vector<int> stones_freq(3, 0);
        for (auto&& stone : stones) {
            stones_freq[stone % 3]++;
        }
        if (stones_freq[0] % 2 == 0) {
            return stones_freq[1] > 0 && stones_freq[2] > 0;
        }
        else {
            return abs(stones_freq[1] - stones_freq[2]) > 2;
        }
    }
};

static void test(vector<int>&& stones) {
    cout << Solution().stoneGameIX(stones) << endl;
}

int main() {
    test(get_list_int("[2,1]"));
    test(get_list_int("[2]"));
    test(get_list_int("[5,1,2,4,3]"));
    return 0;
}
