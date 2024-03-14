// leetcode_Q2485.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

using namespace std;


class Solution {
public:

    static long total(int begin, int include_end) {
        return (begin + include_end) * (include_end - begin + 1) / 2;
    }

    int pivotInteger(int n) {

        for (int i = 1; i <= n; i++) {
            if (total(1, i) == total(i, n)) {
                return i;
            }
        }
        return -1;
    }
};

void test(int n) {
    cout << Solution().pivotInteger(n) << endl;
}


int main()
{
    test(8);
    test(1);
    test(4);
}