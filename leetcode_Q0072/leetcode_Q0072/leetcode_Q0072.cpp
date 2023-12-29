// leetcode_Q0072.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (auto i = 0; i < word1.size() + 1; i++) {
            dp[i][0] = i;
        }
        for (auto j = 0; j < word2.size() + 1; j++) {
            dp[0][j] = j;
        }

        for (auto i = 1; i < word1.size() + 1; i++) {
            for (auto j = 1; j < word2.size() + 1; j++) {
                if (word1[i - 1] != word2[j - 1]) {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                }
                else {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]) + 1);
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};

int main()
{
    cout << Solution().minDistance("horse", "ros") << endl;
    cout << Solution().minDistance("intention", "execution") << endl;
}

