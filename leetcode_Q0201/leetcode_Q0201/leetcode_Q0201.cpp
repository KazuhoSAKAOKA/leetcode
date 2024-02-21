// leetcode_Q0201.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;


class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int value = 0;
        int mask = 0xffffffff;
        for (int i = 0; i < sizeof(int) * 8; i++) {
            const int b = (1 << i);
            if ((left & b) != 0) {
                if ((left & mask) == (right & mask)) {
                    value |= b;
                }
            }
            mask &= ~b;
        }
        return value;
    }
};


void test(int left, int right) {
    cout << Solution().rangeBitwiseAnd(left, right) << endl;
}


int main()
{
    test(12, 15);
    test(5, 7);
    test(0, 0);
    test(1, 2147483647);
}
