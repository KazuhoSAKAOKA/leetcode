// leetcode_Q2379.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int whites = 0;
        int blacks = 0;
        for (int i = 0; i < k; i++) {
            if (blocks[i] == 'W') {
                whites++;
            }
            else {
                blacks++;
            }
        }
        int min_recolors = whites;

        for (int i = k; i < size(blocks); i++) {
            if (blocks[i] == 'W') {
                whites++;
            }
            else {
                blacks++;
            }
            if (blocks[i - k] == 'W') {
                whites--;
            }
            else {
                blacks--;
            }
            min_recolors = min(min_recolors, whites);
        }
        return min_recolors;
    }
};

void test(string&& blocks, int k) {
    cout << Solution().minimumRecolors(blocks, k) << endl;
}

int main()
{
    test("WBBWWBBWBW", 7);
    test("WBWBBBW", 2);
    return 0;
}