// leetcode_Q1550.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <vector>

#include "./../utility/leetcode_testcase_helper.h"
using namespace std;


class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int streak = 0;
        for (auto&& value : arr) {
            if (value % 2 == 1) {
                streak++;
                if (streak == 3) {
                    return true;
                }
            }
            else {
                streak = 0;
            }
        }
        return false;
    }
};

void test(vector<int>&& arr) {
    cout << Solution().threeConsecutiveOdds(arr) << endl;
}

int main()
{
    test(get_list_int("[2,6,4,1]"));
    test(get_list_int("[1,2,34,3,4,5,7,23,12]"));
}