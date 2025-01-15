// leetcode_Q2429.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
using namespace std;

class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int bits = 0;
        for (int i = 0; i < 32; i++) {
            if ((num2 & (1 << i)) != 0) {
                bits++;
            }
        }

        int ans = 0;

        int index = 31;
        while (bits > 0 && index >= 0) {
            const auto bit = 1 << index;
            if ((num1 & bit) != 0) {
                ans |= bit;
                bits--;
            }
            index--;
        }

        index = 0;
        while (bits > 0 && index < 32) {
            const auto bit = 1 << index;
            if ((num1 & bit) == 0) {
                ans |= bit;
                bits--;
            }
            index++;
        }

        return ans;
    }
};

void test(int num1, int num2) {
    cout << Solution().minimizeXor(num1, num2) << endl;
}
int main()
{

    return 0;
}