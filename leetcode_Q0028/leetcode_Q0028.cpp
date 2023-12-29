// leetcode_Q0028.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        const auto it = haystack.find(needle);
        if (it == string::npos)
        {
            return -1;
        }
        return static_cast<int>(it);
    }
};


int main()
{
    const auto ret = Solution().strStr("sadbutsad", "sad");
    //const auto ret = Solution().strStr("leetcode", "leeto");
    std::cout << ret << std::endl;
}

