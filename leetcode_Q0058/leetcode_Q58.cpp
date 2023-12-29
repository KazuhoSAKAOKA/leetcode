// leetcode_Q58.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        auto it = crbegin(s);
        const auto end = crend(s);

        while (it != end && *it == ' ') {
            ++it;
        }
        if (it == end) { return -1; }
        const auto last_ward1 = it;
        while (it != end && *it != ' ') {
            ++it;
        }
        const auto d = std::distance(last_ward1, it);
        return static_cast<int>(d);
    }
};

int main()
{
    std::cout << Solution().lengthOfLastWord("Hello World") << std::endl;
    std::cout << Solution().lengthOfLastWord("   fly me   to   the moon  ") << std::endl;
    std::cout << Solution().lengthOfLastWord("luffy is still joyboy") << std::endl;
    std::cout << Solution().lengthOfLastWord("alpha") << std::endl;
}

