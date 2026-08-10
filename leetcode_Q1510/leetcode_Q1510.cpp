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

    static int rec(long long stones, vector<int>& memo) {
        if (stones == 0) {
            return -1;
        }
        if (memo[stones] != 0) {
            return memo[stones];
        }

        bool exist_win = false;
        for (long long i = 1; i * i <= stones; i++) {
            const auto v = -rec(stones - i * i, memo);
            if (v > 0) {
                exist_win = true;
            }
        }

        memo[stones] = exist_win ? 1 : -1;
        return memo[stones];
    }

    bool winnerSquareGame(int n) {
        vector<int> memo(n + 1);
        const auto r = rec(n, memo);
        return r > 0 ? true : false;
    }
};

static void test(int n) {
    cout << Solution().winnerSquareGame(n) << endl;
}

int main() {
    test(1);
    test(2);
    test(4);
    return 0;
}
