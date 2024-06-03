// leetcode_Q2802.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:


    string kthLuckyNumber(int k) {
        int columns = 1;
        int current = 0;
        int countofcol = 2;
        while ((current + countofcol) < k) {
            current += countofcol;
            countofcol *= 2;
            columns++;
        }
        const auto remain = k - current;
        const auto bits_rep = remain - 1;
        string ans;
        for (int i = 0; i < columns; i++) {
            int b = columns - i - 1;
            if ((1 << b) & bits_rep) {
                ans += '7';
            }
            else {
                ans += '4';
            }
        }

        return ans;
    }
};

void test(int k) {
    cout << Solution().kthLuckyNumber(k) << endl;
}
int main()
{
    test(4);
    test(10);
    test(1000);
}