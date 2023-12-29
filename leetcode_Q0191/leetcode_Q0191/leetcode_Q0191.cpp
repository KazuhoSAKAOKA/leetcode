// leetcode_Q0191.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>


class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for (auto i = 0; i < sizeof(uint32_t) * 8; i++)
        {
            if (n & (1 << i)) { count++; }
        }
        return count;
    }
};
int main()
{
    std::cout << Solution().hammingWeight(0b00000000000000000000000000000000) << std::endl;
    std::cout << Solution().hammingWeight(0b00000000000000000000000000001011) << std::endl;
    std::cout << Solution().hammingWeight(0b00000000000000000000000010000000) << std::endl;
    std::cout << Solution().hammingWeight(0b11111111111111111111111111111101) << std::endl;
}

