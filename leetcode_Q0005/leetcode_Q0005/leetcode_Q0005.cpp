// leetcode_Q0005.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <optional>

using namespace std;

class MySolution {
public:
    vector<vector<optional<bool>>> m_memo;

    bool isPalindromeSub(const string& s, size_t leftIndex, size_t rightIndex)
    {
        if (rightIndex <= leftIndex) { return true; }

        const auto memovalue = m_memo[leftIndex][rightIndex];
        if (memovalue != nullopt) {
            return memovalue.value();
        }
        const auto value = s[leftIndex] == s[rightIndex] && isPalindromeSub(s, leftIndex + 1, rightIndex - 1);
        m_memo[leftIndex][rightIndex] = value;
        return value;
    }

    string longestPalindrome(string s) {

        for (size_t index = 0; index < s.size(); index++)
        {
            vector<optional<bool>> list(s.size(), nullopt);
            m_memo.emplace_back(std::move(list));
        }

        size_t max_index = 0;
        size_t max_length = 0;

        for (size_t left = 0; left < s.size(); left++)
        {
            for (size_t right = left; right < s.size(); right++)
            {
                if (isPalindromeSub(s, left, right)) {
                    const auto len = right - left + 1;
                    if (max_length < len) {
                        max_length = len;
                        max_index = left;
                    }
                }
            }
        }

        return s.substr(max_index, max_length);
    }
};

class DpSolution {
public:



    string longestPalindrome(string s) {

        const auto n = s.size();
        vector<bool> dp(n * n, false);
        
        for (size_t i = 0; i < dp.size(); i++)
        {
            dp[i + i * n] = true;
        }
        size_t max_index = 0;
        size_t max_length = 0;

        for (size_t left = 0; left < s.size(); left++)
        {
            for (size_t right = left + 1; right < s.size(); right++)
            {
                auto index = left + right * n;
                dp[index] = s[left] == s[right] && dp[left + 1, ]
                if (dp[index]) {
                    if (max_length < len) {
                        max_length = len;
                        max_index = left;
                    }
                }
            }
        }

        return s.substr(max_index, max_length);
    }
};


using Solution = MySolution;
using Solution = DpSolution;

int main()
{
    std::cout << Solution().longestPalindrome("babad") << std::endl;
    std::cout << Solution().longestPalindrome("cbbd") << std::endl;
    std::cout << Solution().longestPalindrome("a") << std::endl;

    std::cout << Solution().longestPalindrome("abccba") << std::endl;
}

