// leetcode_Q0007.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cmath>
#include <vector>
#include <minmax.h>
using namespace std;


class Solution {
public:
    int reverse(int x) {
        auto work = abs(x);
        vector<int> nums;
        while (work > 0) {
            nums.push_back(work % 10);
            work /= 10;
        }
        int64_t base = 1;
        int64_t value = 0;
        for (auto it = crbegin(nums); it != crend(nums); ++it) {
            value += base * static_cast<int64_t>(*it);
            base *= 10;
        }

        const auto ret = value * static_cast<int64_t>(x < 0 ? -1 : 1);
        if (ret < INT32_MIN || INT32_MAX < ret) {
            return 0;
        }

        return static_cast<int>(ret);
    }
};

int main()
{
    std::cout << Solution().reverse(123) << std::endl;
    std::cout << Solution().reverse(-123) << std::endl;
    std::cout << Solution().reverse(120) << std::endl;

    std::cout << Solution().reverse(1534236469) << std::endl;
}

