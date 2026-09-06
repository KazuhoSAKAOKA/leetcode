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
#include <bitset>
#include <sstream>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;
class Solution {
public:

    static int rec(const string& s, const string& t, size_t s_index, size_t t_index, vector<vector<int>>& memo) {
        if (size(t) == t_index) { return 1; }
        if (size(s) == s_index) { return 0; }

        if (memo[s_index][t_index] >= 0) {
            return memo[s_index][t_index];
        }
        const auto v1 = rec(s, t, s_index + 1, t_index, memo);
        const auto v2 = s[s_index] == t[t_index] ? rec(s, t, s_index + 1, t_index + 1, memo) : 0;
        memo[s_index][t_index] = v1 + v2;
        return memo[s_index][t_index];
    }

    int numDistinct(string s, string t) {
        const int n = size(s);
        const int m = size(t);
        if (n < m) { return 0; }
        vector<vector<int>> memo(n, vector<int>(m, -1));
        return rec(s, t, 0, 0, memo);
    }
};

static void test(string&& s, string&& t) {
    cout << Solution().numDistinct(s, t) << endl;
}

int main() {
    test("a", "a");
    test("rabbbit", "rabbit");
    test("babgbag", "bag");
    return 0;
}
