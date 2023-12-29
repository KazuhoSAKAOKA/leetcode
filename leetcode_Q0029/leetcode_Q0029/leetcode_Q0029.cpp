// leetcode_Q0029.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <utility>

class Solution {
public:

    static uint64_t mymultiple(uint64_t v1, uint64_t v2) {
        uint64_t total = 0;
        for (auto i = 0; i < 32; i++)
        {
            if ((1 << i) & v2) {
                total += v1 << i;
            }
        }
        return total;
    }

    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }
        const auto dividend_abs = static_cast<uint64_t>(abs(static_cast<int64_t>(dividend)));
        const auto divisor_abs = static_cast<uint64_t>(abs(static_cast<int64_t>(divisor)));
        const bool negative = 0 <= dividend != 0 <= divisor;
        uint64_t range_begin = 0;
        uint64_t range_end = dividend_abs + 1;
        if (range_end < range_begin) {
            std::swap(range_begin, range_end);
        }
        while (range_end - range_begin > 1) {
            const auto value = (range_begin + range_end) >> 1;
            const auto multipled = mymultiple(value, divisor_abs);
            if (multipled == dividend_abs) {
                if (!negative) {
                    return static_cast<int>(value);
                }
                return static_cast<int>(~(value - 1));
            }
            if (multipled < dividend_abs) {
                range_begin = value;
            }
            else {
                range_end = value;
            }
        }
        if (!negative) {
            return static_cast<int>(range_begin);
        }
        return static_cast<int>(~(range_begin - 1));
    }
};


int main()
{
    std::cout << Solution().divide(-2147483648, -1) << std::endl;
    std::cout << Solution().divide(1, 1) << std::endl;

    std::cout << Solution().divide(10, 3) << std::endl;
    std::cout << Solution().divide(7, -3) << std::endl;
}

