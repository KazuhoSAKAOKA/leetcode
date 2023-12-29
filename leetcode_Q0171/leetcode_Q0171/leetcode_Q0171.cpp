// leetcode_Q0171.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    int titleToNumber(string columnTitle) {
        auto it = crbegin(columnTitle);
        int64_t total = *it - 'A' + 1;
        ++it;
        int64_t base = 26;
        for (; it != crend(columnTitle); ++it)
        {
            const auto value = *it - 'A' + 1;
            total += base * value;
            base *= 26;
        }

        return total;
    }
};

int main()
{
    std::cout << Solution().titleToNumber("A") << std::endl;
    std::cout << Solution().titleToNumber("AA") << std::endl;
    std::cout << Solution().titleToNumber("ZY") << std::endl;
}

