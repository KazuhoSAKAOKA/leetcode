// leetcode_q0014.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        const auto strs_begin = cbegin(strs);
        const auto strs_end = cend(strs);
        size_t len = 200;
        for (const auto& s : strs)
        {
            len = min(len, s.length());
        }

        size_t i = 0;
        const auto second = next(strs_begin);
        for (; i < len; i++)
        {
            const auto c = strs[0][i];
            if (!all_of(second, strs_end, [i,c](const auto& s) { return s[i] == c; }))
            {
                break;
            }

        }
        return strs[0].substr(0, i);
    }
};

int main()
{
    //std::vector<string> strs = { "flower", "flow", "flight" };
    //std::vector<string> strs = { "dog","racecar","car" };
    std::vector<string> strs = { "dog", };
    const auto ret = Solution().longestCommonPrefix(strs);
    std::cout << ret << std::endl;
}

