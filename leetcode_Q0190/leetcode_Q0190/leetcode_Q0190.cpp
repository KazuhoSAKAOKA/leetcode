// leetcode_Q0190.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t value = 0;
        for (auto index = 0; index < sizeof(uint32_t) * 8; index++)
        {
            if (n & (1 << index)) {
                value |= (1 << (sizeof(uint32_t) * 8 - index - 1));
            }
        }

        return value;
    }
};

int main()
{
    std::cout << Solution().reverseBits(0b00000010100101000001111010011100) << std::endl;
}

