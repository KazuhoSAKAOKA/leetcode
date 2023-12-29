// leetcode_Q0003.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>

using namespace std;

class Solution {
public:

    pair<int, bool> findIndexFromLast(char c, const string& s, int beginIndex, int length) {
        for (int index = 0; index < length; index++) {
            if (s[beginIndex + length - 1 - index] == c) {
                return make_pair(beginIndex + length - 1 - index, true);
            }
        }
        return make_pair(0, false);
    }

    int getLengthOfLongestSubstringPart(const string& s, int beginIndex, int index) {
        if (s.size() <= index) { return index - beginIndex; }
        const auto& [find_index, result] = findIndexFromLast(s[index], s, beginIndex, index - beginIndex);
        if (!result) {
            return getLengthOfLongestSubstringPart(s, beginIndex, index + 1);
        }
        else {
            const int currentMax = index - beginIndex;
            return max(currentMax, getLengthOfLongestSubstringPart(s, find_index + 1, index + 1));
        }
    }

    int lengthOfLongestSubstring(string s) {
        return getLengthOfLongestSubstringPart(s, 0, 0);
    }
};


int main()
{
    std::cout << Solution().lengthOfLongestSubstring("dvdf") << std::endl;
    std::cout << Solution().lengthOfLongestSubstring("aab") << std::endl;
    std::cout << Solution().lengthOfLongestSubstring("abcabcbb") << std::endl;
    std::cout << Solution().lengthOfLongestSubstring("bbbbb") << std::endl;
    std::cout << Solution().lengthOfLongestSubstring("pwwkew") << std::endl;
    std::cout << Solution().lengthOfLongestSubstring("") << std::endl;
}

