// leetcode_Q1422.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include "./../utility/leetcode_testcase_helper.h"
using namespace std;

class Solution {
public:
    int maxScore(string s) {
        int total_zeros = 0;
        int total_ones = 0;
        for (auto&& c : s) {
            if (c == '0') {
                total_zeros++;
            }
            else {
                total_ones++;
            }
        }

        int max_score = 0;
        int cur_zeros = 0;
        int cur_ones = 0;
        for (int i = 0; i < size(s) - 1; i++) {
            if (s[i] == '0') {
                cur_zeros++;
            }
            else {
                cur_ones++;
            }
            const int cur_score = cur_zeros + (total_ones - cur_ones);
            max_score = max(max_score, cur_score);
        }
        return max_score;
    }
};

static void test(string&& s) {
    cout << Solution().maxScore(s) << endl;
}
int main()
{
    test("011101");
    test("00111");
    test("1111");
    return 0;
}