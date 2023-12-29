// leetcode_Q0043.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:

    void carry(vector<int>& nums, int index) {
        if (nums[index] < 10) { return; }
        nums[index + 1] += nums[index] / 10;
        nums[index] %= 10;
        carry(nums, index + 1);
    }

    string multiply(string num1, string num2) {
        vector<int> nums((num1.size() + 1) * (num2.size() + 1), 0);

        for (auto i = 0; i < num1.size(); i++) {
            for (auto j = 0; j < num2.size(); j++) {
                const auto index1 = num1.size() - 1 - i;
                const auto index2 = num2.size() - 1 - j;
                const auto v1 = num1[index1] - '0';
                const auto v2 = num2[index2] - '0';
                auto val = v1 * v2;
                int index = 0;
                while (val != 0) {
                    nums[i + j + index] += val % 10;
                    carry(nums, i + j + index);
                    val /= 10;
                    index++;
                }

            }
        }

        auto it = crbegin(nums);
        const auto end = crend(nums);
        while (it != end && *it == 0) { ++it; }
        if (it == end) { return "0"; }
        string ret;
        for (;it != end; ++it) {
            ret += (*it) + '0';
        }
        return ret;
    }
};


int main()
{
    std::cout << Solution().multiply("99", "99") << std::endl;
    std::cout << Solution().multiply("999", "999") << std::endl;

    std::cout << Solution().multiply("2", "3") << std::endl;
    std::cout << Solution().multiply("123", "456") << std::endl;
    std::cout << Solution().multiply("0", "0") << std::endl;
}

