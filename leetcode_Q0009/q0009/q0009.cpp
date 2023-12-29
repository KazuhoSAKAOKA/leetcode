// q0009.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <map>
#include <cmath>

using namespace std;


class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) { return false; }
        const int columns = get_mydigits(x);
        for (auto i = 0; i < columns / 2; i++)
        {
            const auto col1 = get_column(x, i);
            const auto col2 = get_column(x, columns - i - 1);
            if (col1 != col2)
            {
                return false;
            }
        }
        return true;
    }

    static int get_mydigits(int value)
    {
        int digits = 0;
        while (value > 0)
        {
            value /= 10;
            digits++;
        }
        return digits;
    }

    static int my_pow(int index)
    {
        if (index == 0) { return 1; }
        const auto it = memo.find(index);
        if (it != cend(memo))
        {
            return it->second;
        }
        const auto value = 10 * my_pow(index - 1);
        memo[index] = value;
        return value;
    }

    static int get_column(int value, int index)
    {
        return (value % my_pow(index + 1)) / my_pow(index);

    }

private:
    static map<int, int> memo;

};

map<int, int> Solution::memo;

int main()
{
    std::cout << Solution::my_pow(2) << std::endl;
    std::cout << Solution::my_pow(3) << std::endl;

    std::cout << Solution::get_column(1234, 2) << std::endl;
    Solution instance;
    std::cout << instance.isPalindrome(123) << std::endl;
    std::cout << instance.isPalindrome(121) << std::endl;
    std::cout << instance.isPalindrome(10) << std::endl;
    std::cout << instance.isPalindrome(11) << std::endl;

}
