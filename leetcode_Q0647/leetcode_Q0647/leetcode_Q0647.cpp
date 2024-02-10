// leetcode_Q0647.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:


    int countSubstrings(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        vector<bool> next(s.size() + 1, false);
        vector<bool> current(s.size() + 1, false);

        dp[0][0] = 1;

        for (int i = 1; i < s.size(); i++) {
            dp[i][0] = dp[i - 1][0] + 1;
            next[0] = true;
            if (s[i] == s[i - 1]) {
                dp[i][1] = dp[i - 1][1] + 1;
                next[1] = true;
            }
            else {
                dp[i][1] = dp[i - 1][1];
                next[1] = false;
            }
            for (int n = 2; n <= i; n++){
                if (current[n - 2] && s[i] == s[i - n]) {
                    dp[i][n] = dp[i - 1][n] + 1;
                    next[n] = true;
                }
                else {
                    dp[i][n] = dp[i - 1][n];
                    next[n] = false;
                }
            }
            swap(current, next);
        }

        int sum = 0;
        for (int i = 0; i < s.size(); i++) {
            sum += dp[s.size() - 1][i];
        }
        return sum;
    }
};



void test(string&& s) {
    cout << Solution().countSubstrings(s) << endl;
}


int main()
{
    Solution2().countSubstrings("fdsklf");

    test("fdsklf");
    test("abc");
    test("aaa");
    test("aaaa");
    test("abccba");
}
