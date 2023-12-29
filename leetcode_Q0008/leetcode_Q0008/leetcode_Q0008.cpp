// leetcode_Q0008.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <minmax.h>
#include <vector>

using namespace std;


class Solution {
public:
    int myAtoi(string s) {
        
        auto it = cbegin(s);
        while (*it == ' ') {
            ++it;
        }

        const bool positive = *it != '-';
        if (*it == '-' || *it == '+') {
            ++it;
        }
        vector<int> nums;
        while (it != cend(s) && isdigit(*it)) {
            nums.emplace_back(static_cast<int>(*it - '0'));
            ++it;
        }

        int value = 0;
        for (auto it1 = cbegin(nums); it1 != cend(nums); ++it1) {
            int pop = *it1 * (positive ? 1 : -1);
            if (value > INT_MAX / 10 || (value == INT_MAX / 10 && pop > 7)) { return INT_MAX; }
            if (value < INT_MIN / 10 || (value == INT_MIN / 10 && pop < -8)) { return INT_MIN; }
            value = value * 10 + pop;
        }

        return value;
    }
};

int main()
{
    cout << Solution().myAtoi("  42") << std::endl;
    cout << Solution().myAtoi("   -42") << std::endl;
    cout << Solution().myAtoi("    +42") << std::endl;
    cout << Solution().myAtoi("42 2") << std::endl;
}

