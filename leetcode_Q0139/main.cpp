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
    bool wordBreak(string s, vector<string>& wordDict) {
        const auto n = size(s);
        vector<bool> dp(n + 1, false);

        auto check = [&](int index, const string& w) {
            if (n - index < size(w)) {
                return;
            }
            for (int j = 0; j < size(w); j++) {
                if (s[index + j] != w[j]) {
                    return;
                }
            }
            dp[index + size(w)] = true;
            };

        dp[0] = true;
        for (int i = 0; i < n; i++) {
            if (dp[i]) {
                for (auto&& word : wordDict) {
                    check(i, word);
                }
            }
        }
        return dp.back();
    }
};

void test(string&& s, vector<string>&& wordDict) {
    cout << Solution().wordBreak(s, wordDict) << endl;
}
int main() {
    test("leetcode", get_list_str(R"(["leet","code"])"));
    test("applepenapple", get_list_str(R"(["apple","pen"])"));
    test("catsandog", get_list_str(R"(["cats","dog","sand","and","cat"])"));
    return 0;
}