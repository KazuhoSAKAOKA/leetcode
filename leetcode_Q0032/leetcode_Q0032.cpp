// leetcode_Q0032.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:

    static int tle(const string& s) {
        int max_len = 0;

        auto check = [&](int x, int len)->bool {
            int current = 0;
            for (int k = 0; k < len; k++) {
                current += s[x + k] == ')' ? -1 : 1;
                if (current < 0) { return false; }
            }
            return current == 0;
            };

        for (int i = 0; i < s.size(); i++) {
            for (int j = max_len + 2; j <= s.size() - i; j += 2) {
                if (check(i, j)) {
                    max_len = max(max_len, j);
                }
            }
        }

        return max_len;
    }

    int longestValidParentheses(string s) {
        vector<int> dp(s.size(), 0);
        int max_len = 0;
        if (!s.empty()) {
            dp[0] = 0;
            for (int i = 1; i < s.size(); i++) {
                if (s[i] == ')') {
                    if (s[i - 1] == '(') {
                        dp[i] = i > 2 ? dp[i - 2] + 2 : 2;
                    }
                    else {
                        if (dp[i - 1] != 0) {
                            if (i > dp[i - 1] - 1) {
                                if (i - dp[i - 1] - 1 < s.size() && s[i - dp[i - 1] - 1] == '(') {
                                    dp[i] = dp[i - 1] + 2;
                                    if (i - dp[i - 1] - 2 < dp.size()) {
                                        dp[i] += dp[i - dp[i - 1] - 2];
                                    }
                                }
                            }
                        }
                    }
                    max_len = max(max_len, dp[i]);
                }
            }
        }
        return max_len;
    }
};

void test(string&& s) {
    cout << Solution().longestValidParentheses(s) << endl;
}

int main()
{
    test("()(())");
    test("(()()");
    test("()(()");
    test(")(");
    test("((()))");
    test("((())))");
    test("(((()))");

    test("(()");
    test(")()())");
    test("");
}