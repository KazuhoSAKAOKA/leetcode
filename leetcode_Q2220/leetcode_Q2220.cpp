// leetcode_Q2220.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class Solution {
public:
    int minBitFlips(int start, int goal) {
        int count = 0;
        for (size_t i = 0; i < 32; i++) {
            const int bit = 1 << i;
            if ((start & bit) != (goal & bit)) {
                count++;
            }
        }
        return count;
    }
};

void test(int start, int goal) {
    cout << Solution().minBitFlips(start, goal) << endl;
}
int main()
{
    test(10, 7);
    test(3, 4);
    return 0;
}