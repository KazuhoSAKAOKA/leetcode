// leetcode_Q0050.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) { return 1; }
        if (n < 0) {
            auto newXX = x * x;
            if (n % 2 == 0) {
                return myPow(newXX, n / 2);
            }
            else {
                return 1 / x * myPow(newXX, (n + 1) / 2);
            }
        }
        return n % 2 != 0 ?
            x * myPow(x * x, (n - 1) / 2) :
            myPow(x * x, n / 2);
    }
};

int main()
{
    std::cout << Solution().myPow(0.00001, 2147483647) << endl;
    std::cout << Solution().myPow(1.00000, -2147483648) << endl;
    std::cout << Solution().myPow(2.0, 10) << endl;
    std::cout << Solution().myPow(2.1, 3) << endl;
    std::cout << Solution().myPow(2.0, -2) << endl;
}

