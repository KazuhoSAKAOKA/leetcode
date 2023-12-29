// leetcode_Q0069.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>


class Solution {
public:


    long long mySqrt(long long x) {
        long long current = 2;
        long long before = 0;
        for(;;)
        {
            const auto value = current * current;
            if (value == x)
            {
                return current;
            }
            if (x < value)
            {
                break;
            }
            else
            {
                before = current;
                current = value;
            }
        }
        for (long long i = current; i > 0; i--)
        {
            if (i * i <= x)
            {
                return i;
            }
        }
        throw 0;
    }
};

int main()
{
    std::cout << Solution().mySqrt(0) << std::endl;
    std::cout << Solution().mySqrt(4) << std::endl;
    std::cout << Solution().mySqrt(8) << std::endl;
    std::cout << Solution().mySqrt(9) << std::endl;
    std::cout << Solution().mySqrt(150) << std::endl;
}

