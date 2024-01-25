// leetcode_Q1143.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));

        for (int i = 0; i < text1.size(); i++) {
            for (int j = 0; j < text2.size(); j++) {
                if (text1[i] == text2[j]) {
                    dp[i + 1][j + 1] = max(dp[i][j] + 1, max(dp[i + 1][j], dp[i][j + 1]));
                }
                else {
                    dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
                }
            }
        }
        return dp[text1.size()][text2.size()];
    }
};

void test(string&& text1, string&& text2) {
    cout << Solution().longestCommonSubsequence(text1, text2) << endl;
}

int main()
{
    test("abcde", "ace");
    test("abc", "abc");
    test("abc", "def");

}