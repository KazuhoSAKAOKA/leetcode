// leetcode_Q0633.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    bool judgeSquareSum(int c) {
        if (c == 0) {
            return true;
        }
        const int upper_limit = sqrt(c);

        for (int i = 0; i <= upper_limit; i++) {
            const auto a2 = i * i;
            const auto remain = c - a2;
            if (remain < 0) { continue; }
            if (remain == 0) {
                return true;
            }
            const int bp = static_cast<int>(sqrt(remain));
            if (bp * bp == remain) {
                return true;
            }
        }
        return false;
    }
};

void test(int c) {
    cout << Solution().judgeSquareSum(c) << endl;
}

int main()
{
    test(11);
    test(0);
    test(5);
    test(3);
    test(2147483647);
}