// leetcode_Q2582.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;

class Solution {
public:
    int passThePillow(int n, int time) {
        const int cycle = n * 2 - 2;
        const int m = time % cycle;
        if (m < n) {
            return m + 1;
        }
        else {
            return (n - 1) - (m - n);
        }
    }
};

void test(int n, int time) {
    cout << Solution().passThePillow(n, time) << endl;
}

int main()
{
    test(4, 5);
    test(3, 2);
}