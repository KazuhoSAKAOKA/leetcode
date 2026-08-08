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
    vector<int> validSequence(string word1, string word2) {
        const int n = size(word1);
        const int m = size(word2);
        vector<int> dp(n + 1);

        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (dp[i + 1] < m) {
                if (word1[i] == word2[m - dp[i + 1] - 1]) {
                    dp[i] = dp[i + 1] + 1;
                }
                else {
                    dp[i] = dp[i + 1];
                }
            }
            else {
                dp[i] = dp[i + 1];
            }
        }

        vector<int> ans;
        ans.reserve(m);
        bool changed = false;
        for (int i = 0; i < n; i++) {
            if (size(ans) == m) { break; }
            if (word1[i] == word2[size(ans)]) {
                ans.push_back(i);
            }
            else if (!changed) {
                if (dp[i + 1] >= m - 1 - size(ans)) {
                    ans.push_back(i);
                    changed = true;
                }
            }
        }
        if (size(ans) < m) { return{}; }

        return ans;
    }
};
static void test(string&& word1, string&& word2) {
    output( Solution().validSequence(word1, word2));
}

int main() {
    test("vbcca","abc");
    test("bacdc", "abc");
    test("aaaaaa", "aaabc");
    test("abc", "ab");
    return 0;
}