// leetcode_Q0476.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class Solution {
public:
    int findComplement(int num) {
        const unsigned int unum = static_cast<unsigned int>(num);
        unsigned int ans = 0;
        int col = 31;
        while (col > 0 && (unum & (1 << col)) == 0) {
            col--;
        }
        for (int i = col; i >= 0; i--) {
            int bit = 1 << i;
            if ((unum & bit)==0) {
                ans |= bit;
            }
        }
        return static_cast<int>(ans);
    }
};

void test(int num) {
    cout << Solution().findComplement(num) << endl;
}
int main()
{
    test(1111);
    test(5);
    test(1);
    return 0;
}