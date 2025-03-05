// leetcode_Q2579.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
using namespace std;
class Solution {
public:
    long long coloredCells(int n) {
        const long long nl = static_cast<long long>(n);
        const long long sq = ((nl - 1) * 2 + 1);
        return sq * sq - 4LL * n * (n - 1LL) / 2LL;
    }
};

void test(int n) {
    cout << Solution().coloredCells(n) << endl;
}
int main()
{
    test(1);
    test(2);
    test(3);
    return 0;
}